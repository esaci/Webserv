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

#	include "w_defines.hpp"
#	include "p_conf.hpp"
#	include "ClassParsingClientRequest.hpp"
#	include "server_data.hpp"

// ces deux suivantes sont les constructor
int				print_return(std::string ptr, int value);
DATA			_data_init(std::string arg);
void			_data_begin(DATA &buff, std::string arg);
char			*_d_s(DATA &arg);


# endif