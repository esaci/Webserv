#include "../include/w_library.hpp"

p_conf(const std::fstream &file): fs(file)
{
	std::string	recvline;

	location_auto_index = false;
	while (std::getline(file, recvline)){
		if (std::strncmp(recvline, "listen ", 7))
			port.assign(recvline.begin + 7, recvline.end());
		else if (std::strncmp(recvline, "root ", 5))
			root.assign(recvline.begin + 5, recvline.end());
		else if (std::strncmp(recvline, "index ", 6))
			index.assign(recvline.begin + 6, recvline.end());
		else if (std::strncmp(recvline, "server_name ", 11))
			server_name.assign(recvline.begin + 6, recvline.end());
		else if (std::strncmp(recvline, "location ", 11))
			location.assign(recvline.begin + 6, recvline.end());
		else if (std::strncmp(recvline, "autoindex on; ", 11))
			location_auto_index = true;
	}
}

~p_conf( void ){
	close(fs);
}