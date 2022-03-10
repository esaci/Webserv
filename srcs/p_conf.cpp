#include "../include/w_library.hpp"

p_conf::p_conf(std::fstream &file)
{
	std::string	recvline;

	location_auto_index = false;
	while (std::getline(file, recvline)){
		if (!std::strncmp(recvline.c_str(), "listen ", 7))
			port.assign(recvline.begin() + 7, recvline.end());
		else if (!std::strncmp(recvline.c_str(), "root ", 5))
			root.assign(recvline.begin() + 5, recvline.end());
		else if (!std::strncmp(recvline.c_str(), "index ", 6))
			index.assign(recvline.begin() + 6, recvline.end());
		else if (!std::strncmp(recvline.c_str(), "server_name ", 11))
			server_name.assign(recvline.begin() + 6, recvline.end());
		else if (!std::strncmp(recvline.c_str(), "location ", 11))
			location.assign(recvline.begin() + 6, recvline.end());
		else if (!std::strncmp(recvline.c_str(), "autoindex on; ", 11))
			location_auto_index = true;
	}
	file.close();
}

p_conf::~p_conf( void ){}