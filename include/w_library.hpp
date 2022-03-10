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
// Ne PAS stocker de donne dans une string, peut poser soucis par la suite
#	include <string>
#	include <fstream>
#	include <cstring>

#	define SERVER_PORT 18000
#	define MAXLINE 4096000
#	define ROOT "/var/www/webserv"
#	define TMPINDEX "/var/www/webserv/index.html"
#	define METHOD	"GET"
#	define TARGET	"/"
#	define SA struct sockaddr
#	define SA_IN struct sockaddr_in
#	define	DATA std::vector<unsigned char>

#	include "p_conf.hpp"

int		_server( void );
int		_response(DATA tmp, DATA tmp2, int connfd);

int		print_return(std::string ptr, int value);

# endif