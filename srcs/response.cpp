#include "../include/w_library.hpp"

void	server_data::check_method(int clientfd)
{
	std::vector<std::string> ma = tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].get_limit_exept((char*)tab_request[clientfd].u_ressource.begin().base());
	std::string method = "";
	for (DATA::iterator it = tab_request[clientfd].method.begin(); it != tab_request[clientfd].method.end(); it++)
		method.append(1, *it);
	for (std::vector<std::string>::iterator it = ma.begin(); it != ma.end(); it++)
	{
		if (*it == method)
			return ;
	}
	tab_request[clientfd].return_error = 405;
}

bool	RP15::_cgi_extensions( void ){
	DATA::iterator temp = ressource.end();
	DATA	tmp_b;

	for (DATA::iterator it = ressource.begin(); it < ressource.end() && *it != '?'; it++)
	{
		if (*it == '.')
			temp = it;
	}
	if (temp == ressource.end())
		return (0);
	if ((size_t)(ressource.end() - temp) < std::strlen(CGI_TYPES))
		return (0);
	tmp_b.assign(temp, temp + std::strlen(CGI_TYPES));
	if (tmp_b == _data_init(CGI_TYPES))
		return (1);
	return (0);
}

int	server_data::_response(int clientfd)
{
	DATA	buff;

	if (tab_request[clientfd].responding == 2)
		return (0);
	check_method(clientfd);
	if (tab_request[clientfd].return_error)
		return (_get_error(clientfd));
	if (tab_request[clientfd].method == _data_init("GET"))
	{
		if (tab_request[clientfd]._cgi_extensions())
			return (tab_request[clientfd]._post_cgi(this, clientfd));
		if ((_data_init("/") == tab_request[clientfd].u_ressource) || tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].map_root.find((char*)tab_request[clientfd].u_ressource.begin().base()) != tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].map_root.end())
			return (_get_index(clientfd));
		return (_get(clientfd));
	}
	else if (tab_request[clientfd].method == _data_init("POST")){
		// 
		if (tab_request[clientfd]._cgi_extensions())
			return (tab_request[clientfd]._post_cgi(this, clientfd));
		return (_post_upload(clientfd));
	}
	else if (tab_request[clientfd].method == _data_init("DELETE")){
		return (delete_request(clientfd)); //elias regarde
	}
	std::cout << tab_request[clientfd].method << " : PARDON ???\n";
	buff = _data_init("HTTP/1.0 200 OK\r\n\r\nHello");
	write(clientfd, buff.begin().base(), buff.size());
	return (-10);
}