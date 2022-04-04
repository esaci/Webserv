#include "../include/w_library.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <map>
#include<string>

/*
    php-cgi testcgi1.php //working test
    php-cgi lol.php //404 test 
*/

void    RP15::set_cgi_env(void){
    std::vector<char *> env;
    std::string content_lengthenv(this->content_length.begin(), this->content_length.end());
    std::string hostenv(this->host.begin(), this->host.end());
    std::string acceptenv(this->accept.begin(), this->accept.end());
    std::string accept_languageenv(this->accept_language.begin(), this->accept_language.end());
    std::string user_agentenv(this->user_agent.begin(), this->user_agent.end());
    std::string methodenv(this->method.begin(), this->method.end());
    
    env.push_back((char *)"SERVER_SOFTWARE=webserv1.0");
    env.push_back((char*)"GATEWAY_INTERFACE=PHP 7.2.24-0ubuntu0.18.04.11");
    env.push_back((char*)"SERVER_PROTOCOL=HTTP/1.1");
    env.push_back((char*)"REDIRECT_STATUS0=200");
  
    // std::string metenv("REDIRECT_STATUS0=");
    // metenv += methodenv;
    // // env.push_back((char*)("REDIRECT_STATUS0=200" += methodenv));
    // std::cout << metenv << "holq\n";
    // env.push_back((char *)metenv.c_str());



    std::string content_lengthv("CONTENT_LENGTH=");
    content_lengthv += content_lengthenv;
    env.push_back((char *)content_lengthv.c_str());
    std::string hostv("SERVER_NAME=");
    hostv += hostenv;
    env.push_back((char *)hostv.c_str());
    std::string acceptv("HTTP_ACCEPT=");
    acceptv += acceptenv;
    env.push_back((char *)acceptv.c_str());
    std::string accept_languagev("HTTP_ACCEPT_LANGUAGE=");
    accept_languagev += accept_languageenv;
    env.push_back((char *)accept_languagev.c_str());
    std::string user_agentv("HTTP_USER_AGENT=");
    user_agentv += user_agentenv;
    env.push_back((char *)user_agentv.c_str());
    std::string methodv("REQUEST_METHOD=");
    methodv += methodenv;
    env.push_back((char *)methodv.c_str());



    //A FINIR IL EN MAQUE COMMENTE EN DESSOUS

    // env["SERVER_NAME="] = hostenv;   //remove :port at end : host name of the server, may be dot-decimal IP address.
    // env["CONTENT_LENGTH="] = content_lengthenv;         
    // env["HTTP_ACCEPT="] = acceptenv;
    // env["HTTP_ACCEPT_LANGUAGE="] = accept_languageenv;  
    // env["HTTP_USER_AGENT="] = user_agentenv;

    // // env["QUERY_STRING="] =   // tout apres le points d'iterrogation
    // // env["CONTENT_TYPE="] =   //type in header 

    // env["REQUEST_METHOD="] = methodenv;

    // //a mettre a jour avec le parsing de raph
    // env["PATH_INFO="] = "/usr/bin/php-cgi";          // path to .php 
    // env["PATH_TRANSLATED="] = "/usr/bin/php-cgi";      // le meme en path absolu
    // env["SCRIPT_NAME="] = "/usr/bin/php-cgi";      //path vers .php : raph 

    for(std::vector<char *>::iterator it = env.begin() ;it != env.end(); it++)
        std::cout << *it << "\n";

    /* optionnal:
    // env.["SERVER_PORT="] =   // a remplir parse port from host          : TCP port (decimal).
    // env.["REMOTE_HOST="] =               
    // env.["REMOTE_ADDR="] =
    // env.["AUTH_TYPE="] =               
    // env.["REMOTE_USER="] = 
    // env.["REMOTE_IDENT="] =               
    // env.["CONTENT_TYPE="] =   //type in header         
    // env.["CONTENT_LENGTH="] = this->content_lenght;//body lenght           
    // env.["HTTP_ACCEPT="] = this->accept;
    // env.["HTTP_ACCEPT_LANGUAGE="] = this->accept_language;               
    // env.["HTTP_USER_AGENT="] = this->user_agent;        
    // env.["HTTP_COOKIE="] =

    */               
}

int RP15::basic_cgi(server_data *s){
    (void)s;
    std::cout << "\nTEST CGI\n\n";
    set_cgi_env();
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
