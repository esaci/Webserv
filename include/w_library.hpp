#ifndef W_LIBRARY_HPP
# define W_LIBRARY_HPP

#	include <sys/socket.h>
#	include <sys/types.h>
#	include <signal.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <string.h>
#	include <unistd.h>
#	include <arpa/inet.h>
#	include <stdarg.h>
#	include <errno.h>
#	include <fcntl.h>
#	include <sys/time.h>
#	include <sys/ioctl.h>
#	include <netdb.h>
#	include <poll.h>
#	include <iostream>
#	include <vector>
#	include <map>
// Ne PAS stocker de donnee dans une string, peut poser soucis par la suite
#	include <string>
#	include <fstream>
#	include <cstring>
#	include <cstdlib>
#	include <sstream>

#	define SERVER_PORT 18000
#	define MAXLINE 4096000
#	define ROOT "/var/www/webserv"
#	define TMPINDEX "/var/www/webserv/index.html"
#	define TMPFAVICO "/var/www/webserv/favicon.ico"
#	define ERRORFILE_400 "./files_system/Bad_Request.html"
#	define ERRORFILE_404 "./files_system/Not_Found.html"
#	define METHOD	"GET"
#	define TARGET	"/"
#	define AUTOINDEX	0
#	define SA struct sockaddr
#	define SA_IN struct sockaddr_in
#	define	DATA std::vector<unsigned char>
#	define C_DATA std::map<int, std::string>
#	define R_DATA ClassParsingClientRequest
#	define CGI "/usr/lib/cgi-bin/php" 
#	include "p_conf.hpp"
#	include "ClassParsingClientRequest.hpp"

int				_server(C_DATA *codes);
int				_response(R_DATA p, int connfd, C_DATA *codes);
C_DATA			*_code_init( void );
int				_get_index(int clientfd, C_DATA *code);
int				_get_favicon(int clientfd, C_DATA *codes);
int				_get_error_400(int clientfd, C_DATA *codes);
int				_get_error_404(int clientfd, C_DATA *codes);
void			_entity(C_DATA *codes, DATA &buff, int code_n, std::string content_type);
void			_entity_no_accept(C_DATA *codes, DATA &buff, int code_n, std::string content_type);

int				print_return(std::string ptr, int value);
std::string		display_code(int n_code, C_DATA *code);
DATA			_data_init(std::string arg);
void			_data_begin(DATA &buff, std::string arg);


# endif