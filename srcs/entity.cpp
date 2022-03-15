#include "../include/w_library.hpp"

void	server_data::_entity(DATA &buff, int code_n, std::string content_type){
	std::stringstream out;
	out << "HTTP/1.1 "<< display_code(code_n) << "\r\n";
	out << "Server: webserv/1.0\n";
	out << "Content-Type: " << content_type << "\n";
	out << "Content-Length: " << buff.size() << "\n";
	out << "Connection: close\n";
	out << "Accept-Ranges: bytes\r\n\r\n";
	_data_begin(buff, out.str());
}

void	server_data::_entity_no_accept(DATA &buff, int code_n, std::string content_type){
	std::stringstream out;
	out << "HTTP/1.1 "<< display_code(code_n) << "\r\n";
	out << "Server: webserv/1.0\n";
	out << "Content-Type: " << content_type << "\n";
	out << "Content-Length: " << buff.size() << "\n";
	out << "Connection: close\r\n\r\n";
	_data_begin(buff, out.str());
}