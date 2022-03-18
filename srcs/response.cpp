#include "../include/w_library.hpp"

int	server_data::_response(int clientfd)
{
	DATA	buff;
	int		n;

	if (tab_request[clientfd].method == _data_init("GET"))
	{
		// Il faudra rajouter la condition si on prend en ressource lindex directement
		// Faudra ameliorer ce if
		if ((_data_init("/") == tab_request[clientfd].ressource) || (_data_init(TMPINDEX) == tab_request[clientfd].ressource))
			return (_get_index(clientfd));
		if (_data_init("/favicon.ico") == tab_request[clientfd].ressource)
			return (_get_favicon(clientfd));
		if (AUTOINDEX)
			return(_get_error_400(clientfd));
		return(_get_error_404(clientfd));
	}
	// std::cout << tab_request[clientfd].method << " : PARDON ???\n";
	buff = _data_init("HTTP/1.0 200 OK\r\n\r\nHello");
	n = write(clientfd, buff.begin().base(), buff.size());
	return (n);
}