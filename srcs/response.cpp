#include "../include/w_library.hpp"

int	server_data::_response(int clientfd)
{
	DATA	buff;

	if (tab_request[clientfd].responding == 2)
		return (0);
	if (tab_request[clientfd].return_error)
		return (_get_error(clientfd));
	if (tab_request[clientfd].method == _data_init("GET"))
	{
		if ((_data_init("/") == tab_request[clientfd].ressource) || (_data_init(TMPINDEX) == tab_request[clientfd].ressource))
			return (_get_index(clientfd));
		return (_get(clientfd));
	}
	else if (tab_request[clientfd].method == _data_init("POST")){
		return (tab_request[clientfd]._post_cgi(this, clientfd));
	}
	std::cout << tab_request[clientfd].method << " : PARDON ???\n";
	buff = _data_init("HTTP/1.0 200 OK\r\n\r\nHello");
	write(clientfd, buff.begin().base(), buff.size());
	return (-10);
}