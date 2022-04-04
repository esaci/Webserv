#include "../include/w_library.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
	php-cgi testcgi1.php //working test
	php-cgi lol.php //404 test 
*/

void	set_cgi_env(){

}

int RP15::basic_cgi(server_data *s, int fd){
	char **args = (char **)malloc(sizeof(char *) * 3);
	args[0] = strdup("/usr/bin/php-cgi"); //CHECK WITH PARSIng  
	args[1] = strdup("./files_test/testcgi1.php"); //REPLACE WITH FILE VAUE SENT BY RAPH /BIN/CGI ETC
	args[2] = NULL;

	// dup2()
	int		ret = 1;
	pid_t	pid = fork();
	int		status;
	if (pid < 0)
		return (print_return("error: fork", 1));
	if (!pid)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ret = execve(args[0], args, NULL);
		delete s;
		for(int i = 0; i < 3 && args[i]; i++)
			free(args[i]);
		if(args)
			free(args);
		exit(ret);
	}
	else
		waitpid(pid, &status, 0);
	for(int i = 0; i < 3 && args[i]; i++)
		free(args[i]);
	if(args)
		free(args);
	if(fd != -1)
		close(fd);
	return 0;
}
