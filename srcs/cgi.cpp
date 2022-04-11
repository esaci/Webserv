#include "../include/w_library.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <map>
#include<string>

/*
	php-cgi testcgi1.php //working test
	php-cgi lol.php //404 test
    siege -c10 -r20 127.0.0.1:18000
    stress test is 10 users 20 requests running on vm only 
*/

int RP15::set_cgi_env(server_data *s, int fd){

    int		ret = 1;
	pid_t	pid = fork();
    int     status;
    
    std::vector<char *> env;
    std::string cgipath(CGI);                // mettre a jour avec parsing raph
    std::string content_lengthenv(this->content_length.begin(), this->content_length.end());
    std::string hostenv(this->host.begin(), this->host.end());
    std::string acceptenv(this->accept.begin(), this->accept.end());
    std::string accept_languageenv(this->accept_language.begin(), this->accept_language.end());
    std::string user_agentenv(this->user_agent.begin(), this->user_agent.end());
    std::string methodenv(this->method.begin(), this->method.end());
    std::string content_typeenv(this->content_type.begin(), this->content_type.end());
    std::string r_body_bufferenv(this->r_body_buffer.begin(), this->r_body_buffer.end());
        // std::string r_body_getenv(++this->r_body_get.begin(), this->r_body_get.end());

    env.push_back(const_cast<char*>("SERVER_SOFTWARE=webserv1.0"));
    env.push_back(const_cast<char*>("GATEWAY_INTERFACE=CGI/1.1"));
    env.push_back(const_cast<char*>("SERVER_PROTOCOL=HTTP/1.1"));
    env.push_back(const_cast<char*>("REDIRECT_STATUS=200"));
    std::string content_lengthv("CONTENT_LENGTH=");
    // std::cout << content_lengthenv << content_length << "lol\n";
    // if(content_lengthenv.size() == 0){
        content_lengthv.append(content_lengthenv);
    // }
    env.push_back(const_cast<char*>(content_lengthv.c_str()));
    std::string hostv("SERVER_NAME=webserv");
    // hostv += hostenv;
    // hostv += "\0";
    
    env.push_back(const_cast<char*>(hostv.c_str()));
    std::string acceptv("HTTP_ACCEPT=");
    acceptv += acceptenv;
    env.push_back(const_cast<char*>(acceptv.c_str()));
    std::string accept_languagev("HTTP_ACCEPT_LANGUAGE=");
    accept_languagev += accept_languageenv;
    env.push_back(const_cast<char*>(accept_languagev.c_str()));
    std::string user_agentv("HTTP_USER_AGENT=");
    user_agentv += user_agentenv;
    env.push_back(const_cast<char*>(user_agentv.c_str()));
    std::string methodv("REQUEST_METHOD=");
    methodv += methodenv;
    env.push_back(const_cast<char*>(methodv.c_str()));


std::string ressourceenv(ressource.begin(), ressource.end());
    std::string path_infov("PATH_INFO=");
    // path_infov += cgipath; //est ce le bout de l url apres ?
    // path_infov += ressourceenv;
    env.push_back(const_cast<char*>(path_infov.c_str()));
    std::string path_translatedv("PATH_TRANSLATED=");
    // path_translatedv += cgipath; //all path
    std::string path("/goinfre/ogenser/Webserv/files_test/vfirst_test_php.php");
    path_translatedv += path;
    // path_translatedv += ressourceenv;
    env.push_back(const_cast<char*>(path_translatedv.c_str()));
    std::string script_namev("SCRIPT_NAME=");
    script_namev += ressourceenv;
    // if(methodenv == "POST")
    //     script_namev += r_body_bufferenv; // A REMPLACER PAR LE PATH DE RAPH
    // else if (methodenv == "GET")
    //     script_namev += r_body_getenv;
    env.push_back(const_cast<char*>(script_namev.c_str()));

    std::string query_stringv("QUERY_STRING=");
    // std::cout << r_body_bufferenv << "MES COULLES\n";

    
    if(methodenv == "POST")
        query_stringv += r_body_bufferenv; // probleme valgrind
    else if (methodenv == "GET"){
        std::string r_body_getenv(++this->r_body_get.begin(), this->r_body_get.end());
        query_stringv += r_body_getenv;
    }
    env.push_back(const_cast<char*>(query_stringv.c_str()));

    std::string content_typev("CONTENT_TYPE=");
    content_typev += content_typeenv; 
    env.push_back(const_cast<char*>(content_typev.c_str()));


    std::string server_portv("SERVER_PORT=0");
    env.push_back(const_cast<char*>(server_portv.c_str()));

    std::string remote_addrv("REMOTE_ADDR=0.0.0.0");
    env.push_back(const_cast<char*>(remote_addrv.c_str()));

    env.push_back(NULL);
    // int i = 0;
    // for(std::vector<char *>::iterator it = env.begin() ;it != env.end(); it++, i++){
    //     ev[i] = *it;
    //     // std::cout << ev[i] << "hello\n";
    // }
    // ev[i] = NULL;

    ev = env.data();
    // ev[env.size() + 1] = NULL;

    // char **args = (char **)malloc(sizeof(char *) * 3);
	//     args[0] = strdup(CGI);
	//     args[1] = (char *)ressourceenv.c_str();
    //     args[2] = NULL;


    // execve(CGI, args, ev);
    // for (size_t i = 0; i < 17; i++){
    //     // ev[i][1] = '\0'; 
    //     std::cout << ev[i] << "\n";
    // }
    // exit(0);


    if (pid < 0)
		return (print_return("error: fork", 1));

	if (!pid)
	{
         for (size_t i = 0; i < 17; i++){
        // ev[i][1] = '\0'; 
        std::cout << i << " "<< ev[i] << "\n";
        if(ev[i] == NULL)
            std::cout << "C NULLLL\n";
    }
        ev[16] = NULL;
        char **args = (char **)malloc(sizeof(char *) * 3);
	    args[0] = strdup(CGI);
	    args[1] = (char *)ressourceenv.c_str();
        args[2] = NULL;
        std::cout << "C NULLLL\n";
        for (size_t i = 0; i < 3; i++){
            std::cout << args[i] << "\n";
        }
		dup2(fd, 1);
		// close(fd);
		ret = execve(CGI, args, ev);

          for (size_t i = 0; i < 15; i++){
        // ev[i][1] = '\0'; 
        std::cout << "ok"<< ev[i] << "\n";
    }

		delete s;
        if(args[0])
		    free(args[0]);
		if(args)
			free(args);
		exit(ret);
	}
    else{
        waitpid(pid, &status, 0);
    }
	if(fd != -1)
		close(fd);

    return 0;
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


void RP15::test(void){
    std::vector<char *> env;
    // char **caca;
    env.push_back((char *)"SERVER_SOFTWARE=webserv1.0\0");
    ev[0] = env[0];
    // return lol;
}

int RP15::basic_cgi(server_data *s, int fd){
    // ressource = u_ressource;
	ressource = _link_root_init(s->tab_tab_ap[s->sockets_to_hosts[serverfd]][0].get_root((char*)u_ressource.begin().base()), ressource);
	std::cout << "\n" << ressource << std::endl;
	std::cout << "BODY " << r_body_buffer << "|\n";
    
	/*
	if (FICHIER PAS OUVERT)
	{
		tab_request[clientfd].return_error = 404;
		_get_error_404(clientfd);
	} 
	 */
	// POUR GET CA SERA r_body_get, linput apres le ?
    // std::cout << "caca" << r_body_buffer << "lol" << CGI;
	// int		ret = 1;
	// pid_t	pid = fork();
    // int     status;
    std::string ressourceenv(ressource.begin(), ressource.end());

    // for (size_t i = 0; i < 16; i++)
    // {
    //     std::cout << i << set_cgi_env()[i] << " cac\n";
    //     // if(set_cgi_env()[i] == NULL)
    //     //     std::cout << "NULL" << i << "\n";
    // }
    // std::cout << test() << "\n";
   
   set_cgi_env(s, fd);
   std::cout << "hello\n" << "\n";
   
    // std::cout << "HELLO\n\n\n\n";
    // for (size_t i = 0; i < 15; i++)
    //     std::cout << this->ev[i] << "\n";
    // exit(0);
    

	// if (pid < 0)
	// 	return (print_return("error: fork", 1));

	// if (!pid)
	// {
    //     char **args = (char **)malloc(sizeof(char *) * 3);
	//     args[0] = strdup(CGI);
	//     args[1] = (char *)ressourceenv.c_str();
    //     args[2] = NULL;
	// 	dup2(fd, STDOUT_FILENO);
	// 	close(fd);
	// 	ret = execve(CGI, args, NULL);
	// 	delete s;
    //     if(args[0])
	// 	    free(args[0]);
	// 	if(args)
	// 		free(args);
	// 	exit(ret);
	// }
    // else{
    //     waitpid(pid, &status, 0);
    // }
	// if(fd != -1)
	// 	close(fd);
	return 0;
}

