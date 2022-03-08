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

#	include <iostream>
#	include <vector>
// Ne PAS stocker de donne dans une string, peut poser soucis par la suite
#	include <string>
#	include <fstream>

#	define SERVER_PORT 18000
#	define MAXLINE 4096
#	define SA struct sockaddr
#	define SA_IN struct sockaddr_in

int	_server( void );



# endif