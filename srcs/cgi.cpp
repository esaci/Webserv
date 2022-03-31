#include "../include/w_library.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    php-cgi testcgi1.php //working test
    php-cgi lol.php //404 test 
*/

void    set_cgi_env(){

}

int basic_cgi(void){
    std::cout << "\nTEST CGI\n\n";

    char **args = (char **)malloc(sizeof(char *) * 3);
    args[0] = strdup("/usr/bin/php-cgi"); //CHECK WITH PARSIng  
    args[1] = strdup("./files_test/testcgi1.php"); //REPLACE WITH FILE VAUE SENT BY RAPH /BIN/CGI ETC
    args[2] = NULL;
    // dup2()
	int		ret = 1;
	pid_t	pid = fork();
    int     status;
    int fd = -1;

	if (pid < 0)
		std::cout << "error: fork\n";
	if (pid == 0){
        waitpid(pid, &status, 0);
    }
	else{
        fd = open("mabite.html", O_RDWR | O_CREAT | O_TRUNC, 0666);
        dup2(fd, STDOUT_FILENO);
        ret = execve(args[0], args, NULL);
        exit(ret);
    }

	// // 	// ret = ft_parent(c, s);
    // // if(err == -1){
    // //     return -1;}
	// return (ret);
    if(fd != -1)
        close(fd);
    for(int i = 0; i < 3 && args[i]; i++)
        free(args[i]);
    if(args)
        free(args);
    return 0;
}
