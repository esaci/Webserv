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

char    **RP15::set_cgi_env(void){
    std::vector<char *> env;
    std::string cgipath(CGI);                // mettre a jour avec parsing raph
    std::string content_lengthenv(this->content_length.begin(), this->content_length.end());
    std::string hostenv(this->host.begin(), this->host.end());
    std::string acceptenv(this->accept.begin(), this->accept.end());
    std::string accept_languageenv(this->accept_language.begin(), this->accept_language.end());
    std::string user_agentenv(this->user_agent.begin(), this->user_agent.end());
    std::string methodenv(this->method.begin(), this->method.end());
    
    env.push_back((char *)"SERVER_SOFTWARE=webserv1.0");
    env.push_back((char*)"GATEWAY_INTERFACE=CGI/1.1");
    env.push_back((char*)"SERVER_PROTOCOL=HTTP/1.1");
    env.push_back((char*)"REDIRECT_STATUS=200");
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
    std::string path_infov("PATH_INFO=");
    path_infov += cgipath; //est ce le bout de l url apres ?
    env.push_back((char *)path_infov.c_str());
    std::string path_translatedv("PATH_TRANSLATED=");
    path_translatedv += cgipath; //all path
    env.push_back((char *)path_translatedv.c_str());
    std::string script_namev("SCRIPT_NAME=");
    // script_namev += cgipath; // a commencer par un /
    script_namev += "/home/user42/Bureau/webserv/files_test/testcgi1.php"; // A REMPLACER PAR LE PATH DE RAPH
    env.push_back((char *)script_namev.c_str());
    std::string query_stringv("QUERY_STRING=");
    query_stringv += "pseudo=sh";       //est ce le bout de l url apres ?  ou le  body // var par elias
    env.push_back((char *)query_stringv.c_str());
    std::string content_typev("CONTENT_TYPE=");
    content_typev += "application/x-www-form-urlencoded" ;             // var par elias
    env.push_back((char *)content_typev.c_str());


    int i = 0;
    for(std::vector<char *>::iterator it = env.begin() ;it != env.end(); it++, i++){
        ev[i] = *it;
        std::cout << ev[i] << "\n";
    }
    return ev;

    /* optionnal:
    // "SERVER_PORT=" // a remplir parse port from host          : TCP port (decimal).
    // "REMOTE_HOST="               
    // "REMOTE_ADDR="
    // "AUTH_TYPE="              
    // "REMOTE_USER=" 
    // "REMOTE_IDENT="                             
    // "HTTP_COOKIE="
    request uri
    */               
}

int RP15::basic_cgi(server_data *s, int fd){
	ressource = _link_root_init(s->tab_tab_ap[*(s->tab_ap.find(s->sockets_to_hosts[serverfd]))][0].get_root((char*)ressource.begin().base()), ressource);
	std::cout << "\n" << ressource << std::endl;
	std::cout << "BODY " << r_body_buffer << "|\n";
    //important checker l'histoire des fds de la correction avec select //elias
	// REMPLACER CONTENT TYPE content_type
	/*
	if (FICHIER PAS OUVERT)
	{
		tab_request[clientfd].return_error = 404;
		_get_error_404(clientfd);
	} 
	 */
	// POUR GET CA SERA r_body_get, linput apres le ?
	int		ret = 1;
	pid_t	pid = fork();

    int     status;

    std::cout << "\nTEST CGI\n\n";
    set_cgi_env();

	if (pid < 0)
		return (print_return("error: fork", 1));

    char **args = (char **)malloc(sizeof(char *) * 3);
	args[0] = strdup(CGI); //CHECK WITH PARSIng raph
	args[1] = strdup("./files_test/testcgi1.php"); //REPLACE WITH FILE VALUE SENT BY RAPH /BIN/CGI ETC
    args[2] = NULL;
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
    else{
        waitpid(pid, &status, 0);
	    for(int i = 0; i < 3 && args[i]; i++)
		    free(args[i]);
	    if(args)
		    free(args);
    }
	if(fd != -1)
		close(fd);
	return 0;
}

