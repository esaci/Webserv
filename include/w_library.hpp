#ifndef W_LIBRARY_HPP
# define W_LIBRARY_HPP

#	include <sys/socket.h>
#	include <sys/types.h>
#	include <sys/stat.h>
#	include <signal.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <string.h>
#	include <unistd.h>
#	include <ctime>
#	include <arpa/inet.h>
#	include <stdarg.h>
#	include <errno.h>
#	include <fcntl.h>
#	include <dirent.h>
#	include <sys/time.h>
#	include <sys/ioctl.h>
#	include <netdb.h>
#	include <poll.h>
#	include <iostream>
#	include <vector>
#	include <map>
#	include <set>
// Ne PAS stocker de donnee dans une string, peut poser soucis par la suite
#	include <string>
#	include <fstream>
#	include <cstring>
#	include <cstdlib>
#   include <cctype>
#	include <sstream>

#	include "w_defines.hpp"
#	include "p_conf.hpp"
#	include "ClassParsingClientRequest.hpp"
#	include "server_data.hpp"
#	include "indexcomp.hpp"

int				print_return(std::string ptr, int value);
DATA			_data_init(std::string arg);
void			_data_begin(DATA &buff, std::string arg);
void			_data_end(DATA &buff, std::string arg);
char			*_d_s(DATA &arg);
DATA			_link_root_init(std::string root, DATA &ressource);
size_t			hexa_to_dec(DATA &buff);
void			dec_to_hexa(DATA &buff, DATA::iterator it, size_t decimal_value);
bool			compare_size_cl(size_t len, DATA &buff);
DATA			retire_root(DATA &buff, std::string &root);
void	        retire_tiret(DATA &buff);
std::vector<struct pollfd>::iterator    _return_it_poll(int clientfd, std::vector<struct pollfd> &tab_poll);
void			_erase_location(DATA &ressource, _MAP_ROOT &map_root, std::string &root);

# endif