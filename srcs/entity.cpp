#include "../include/w_library.hpp"

void	server_data::_entity(int code_n, int clientfd){
	std::string content_type = _entity_ctype(clientfd); 
	std::stringstream out;

	out << "HTTP/1.1 "<< display_code(code_n) << "\r\n";
	out << "Server: webserv/1.0\r\n";
	if (content_type[0])
		out << "Content-Type: " << content_type << "\r\n";
	out << "Content-Length: " << tab_request[clientfd].r_buffer.size() << "\r\n";
	if (code_n == 301)
		out << "Location: " << "http://" << sockets_to_hosts[tab_request[clientfd].serverfd].first << ":" << sockets_to_hosts[tab_request[clientfd].serverfd].second << tab_request[clientfd].redirection << " \r\n";
	if (code_n != 100)
		out << "Connection: close\r\n";
	if (code_n != 301)
		out << "Accept-Ranges: bytes\r\n";
	out << "\r\n";
	_data_begin(tab_request[clientfd].r_buffer, out.str());
}

void	server_data::_entity_no_accept(int code_n, int clientfd){
	std::stringstream out;
	std::string content_type = _entity_ctype(clientfd); 
	
	out << "HTTP/1.1 "<< display_code(code_n) << "\r\n";
	out << "Server: webserv/1.0\r\n";
	if (content_type[0])
		out << "Content-Type: " << content_type << "\r\n";
	out << "Content-Length: " << tab_request[clientfd].r_buffer.size() << "\r\n";
	if (code_n == 301)
		out << "Location: " << sockets_to_hosts[tab_request[clientfd].serverfd].first << sockets_to_hosts[tab_request[clientfd].serverfd].second << tab_request[clientfd].redirection << " \r\n";
	out << "Connection: close\r\n";
	out << "\r\n";
	_data_begin(tab_request[clientfd].r_buffer, out.str());
}

std::string	server_data::_entity_ctype(int clientfd){
	std::string		tmp_ctype;
	size_t i = 0;

	if (!tab_request[clientfd].ressource.begin().base())
		return (tmp_ctype);
	const char*tmp_char = (char*)(tab_request[clientfd].ressource.begin().base());
	tmp_ctype.assign(tmp_char, tab_request[clientfd].ressource.size());
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