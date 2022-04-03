#include "../include/w_library.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    php-cgi testcgi1.php //working test
    php-cgi lol.php //404 test 
*/

void    set_cgi_env(){
    map env<std::string, std::string> env;
    env.["SERVER_SOFTWARE="] "webserv1.0";
    env.["SERVER_NAME="] = ;          : host name of the server, may be dot-decimal IP address.
    env.["GATEWAY_INTERFACE="] = "PHP 7.2.24-0ubuntu0.18.04.11";               : CGI/version.
    env.["SERVER_PROTOCOL="] = "HTTP/1.1"               : HTTP/version.
    env.["SERVER_PORT="] =   // a remplir            : TCP port (decimal).
    env.["REQUEST_METHOD="] =   // a remplir         : name of HTTP method (see above).
    env.["PATH_INFO="] =               : path suffix, if appended to URL after program name and a slash.
    env.["PATH_TRANSLATED="] =               : corresponding full path as supposed by server, if PATH_INFO is present.
    env.["SCRIPT_NAME="] =               : relative path to the program, like /cgi-bin/script.cgi.
    env.["QUERY_STRING="] =               
    env.["REMOTE_HOST="] =               
    env.["REMOTE_ADDR="] =               
    env.["AUTH_TYPE="] =               
    env.["REMOTE_USER="] = 
    env.["REMOTE_IDENT="] =               
    env.["CONTENT_TYPE="] =               
    env.["CONTENT_LENGTH="] =               
    env.["HTTP_ACCEPT="] =                
    env.["HTTP_ACCEPT_LANGUAGE="] =                
    env.["HTTP_USER_AGENT="] =               
    env.["HTTP_COOKIE="] =               
}

int RP15::basic_cgi(server_data *s){
    (void)s;
    std::cout << "\nTEST CGI\n\n";
    // std::cout <<
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
        delete s;
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
