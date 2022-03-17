#include "../include/w_library.hpp"

void	server_data::_entity(int code_n, std::string content_type){
	std::stringstream out;

	out << "HTTP/1.1 "<< display_code(code_n) << "\r\n";
	out << "Server: webserv/1.0\n";
	if (content_type[0])
		out << "Content-Type: " << content_type << "\n";
	out << "Content-Length: " << parse_temp.size() << "\n";
	out << "Connection: close\n";
	out << "Accept-Ranges: bytes\r\n\r\n";
	_data_begin(parse_temp, out.str());
}

void	server_data::_entity_no_accept(int code_n, std::string content_type){
	std::stringstream out;

	out << "HTTP/1.1 "<< display_code(code_n) << "\r\n";
	out << "Server: webserv/1.0\n";
	if (content_type[0])
		out << "Content-Type: " << content_type << "\n";
	out << "Content-Length: " << parse_temp.size() << "\n";
	out << "Connection: close\r\n\r\n";
	_data_begin(parse_temp, out.str());
}

std::string	server_data::_entity_ctype(int clientfd){
	std::string		tmp_ctype;
	size_t i = 0;

	if (!tab_request[clientfd].ressource.begin().base())
		return (tmp_ctype);
	const char*tmp_char = (char*)(tab_request[clientfd].ressource.begin().base());
	tmp_ctype.assign(tmp_char);
	while (i < tmp_ctype.size()){
		for (i = 0; i < tmp_ctype.size() && tmp_ctype[i] != '.'; i++)
			;
		if (i < tmp_ctype.size())
		{
			tmp_ctype.assign(tmp_ctype.c_str() + i + 1);
			i = 0;
		}
	}
	return (ctypes[tmp_ctype]);
}