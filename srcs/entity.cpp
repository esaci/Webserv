#include "../include/w_library.hpp"

void	_entity(C_DATA *codes, DATA &buff, int code_n, std::string content_type){
	std::stringstream out;
	out << "HTTP/1.1 "<< display_code(code_n, codes) << "\r\n";
	out << "Server: webserv/1.0\n";
	out << "Content-Type: " << content_type << "\n";
	out << "Content-Length: " << buff.size() << "\n";
	out << "Connection: close\n";
	out << "Accept-Ranges: bytes\r\n\r\n";
	_data_begin(buff, out.str());
}

void	_entity_no_accept(C_DATA *codes, DATA &buff, int code_n, std::string content_type){
	std::stringstream out;
	out << "HTTP/1.1 "<< display_code(code_n, codes) << "\r\n";
	out << "Server: webserv/1.0\n";
	out << "Content-Type: " << content_type << "\n";
	out << "Content-Length: " << buff.size() << "\n";
	out << "Connection: close\r\n\r\n";
	_data_begin(buff, out.str());
}