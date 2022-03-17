#include "../include/w_library.hpp"

p_conf::p_conf(std::fstream &file)
{
	std::string	tmp;

	location_auto_index = false;
	while (std::getline(file, tmp)){
		if (!std::strncmp(tmp.c_str(), "listen ", 7))
			port.assign(tmp.begin() + 7, tmp.end());
		else if (!std::strncmp(tmp.c_str(), "root ", 5))
			root.assign(tmp.begin() + 5, tmp.end());
		else if (!std::strncmp(tmp.c_str(), "index ", 6))
			index.assign(tmp.begin() + 6, tmp.end());
		else if (!std::strncmp(tmp.c_str(), "server_name ", 11))
			server_name.assign(tmp.begin() + 6, tmp.end());
		else if (!std::strncmp(tmp.c_str(), "location ", 11))
			location.assign(tmp.begin() + 6, tmp.end());
		else if (!std::strncmp(tmp.c_str(), "autoindex on; ", 11))
			location_auto_index = true;
	}
	file.close();
}

p_conf::~p_conf( void ){}