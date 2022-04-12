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

    env.push_back(const_cast<char*>("SERVER_SOFTWARE=webserv1.0"));
    env.push_back(const_cast<char*>("GATEWAY_INTERFACE=CGI/1.1"));
    env.push_back(const_cast<char*>("SERVER_PROTOCOL=HTTP/1.1"));
    env.push_back(const_cast<char*>("REDIRECT_STATUS=200"));
    std::string content_lengthv("CONTENT_LENGTH=");
    content_lengthv.append(content_lengthenv);
    env.push_back(const_cast<char*>(content_lengthv.c_str()));
    std::string hostv("SERVER_NAME=webserv");
    // hostv += hostenv;    
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
    path_infov += ressourceenv;
    env.push_back(const_cast<char*>(path_infov.c_str()));
    std::string path_translatedv("PATH_TRANSLATED=");
    // path_translatedv += cgipath; //all path
    // std::string path("/sgoinfre/goinfre/Perso/ogenser/webservfinish/files_test/vfirst_test_phppost.php"); // reaplce
    // path_translatedv += path;
    path_translatedv += ressourceenv;
    env.push_back(const_cast<char*>(path_translatedv.c_str()));
    std::string script_namev("SCRIPT_NAME=");
    script_namev += ressourceenv;
    env.push_back(const_cast<char*>(script_namev.c_str()));

    std::string query_stringv("QUERY_STRING=");
    if (methodenv == "GET"){
        std::string r_body_getenv(++this->r_body_get.begin(), this->r_body_get.end());
        query_stringv += r_body_getenv;
    }
    env.push_back(const_cast<char*>(query_stringv.c_str()));

    std::string content_typev("CONTENT_TYPE=");
    content_typev += content_typeenv; 
    env.push_back(const_cast<char*>(content_typev.c_str()));
    std::string server_portv("SERVER_PORT=");
    env.push_back(const_cast<char*>(server_portv.c_str()));
    std::string remote_addrv("REMOTE_ADDR=");
    env.push_back(const_cast<char*>(remote_addrv.c_str()));
    env.push_back(NULL);

    ev = env.data();

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

        int fdbody = 0;
        if(methodenv == "POST"){
            fdbody = open("./files_system/cgi-in", O_RDWR, 0666);
            lseek(fdbody, 0, SEEK_SET);
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
		dup2(fd, STDOUT_FILENO);
        if(methodenv == "POST"){
            dup2(fdbody, STDIN_FILENO);
            // close(fdbody);
        }
		close(fd);
		ret = execve(CGI, args, ev);

        //   for (size_t i = 0; i < 15; i++){
        //     // ev[i][1] = '\0'; 
        //     std::cout << "ok"<< ev[i] << "\n";
        // }

		delete s;
        if(args[0])
		    free(args[0]);
		if(args)
			free(args);
        //return an error 500 caus execve is crashed
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


int RP15::basic_cgi(server_data *s, int fd){
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

    std::string ressourceenv(ressource.begin(), ressource.end());
   
   set_cgi_env(s, fd);
   std::cout << "hello\n" << "\n";
   std::cout << ressourceenv << "jshgd\n";

	return 0;
}

