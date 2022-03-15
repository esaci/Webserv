#include "../include/w_library.hpp"

int	server_data::_response(R_DATA p, int clientfd)
{
	DATA	buff;
	int		n;

	if (p.method == _data_init("GET"))
	{
		// Il faudra rajouter la condition si on prend en ressource lindex directement
		// Faudra ameliorer ce if
		if ((_data_init("/") == p.ressource) || (_data_init(TMPINDEX) == p.ressource))
			return (_get_index(clientfd));
		if (_data_init("/favicon.ico") == p.ressource)
			return (_get_favicon(clientfd));
		if (AUTOINDEX)
			return(_get_error_400(clientfd));
		return(_get_error_404(clientfd));
	}
	buff = _data_init("HTTP/1.0 200 OK\r\n\r\nHello");
	n = write(clientfd, buff.begin().base(), buff.size());
	return (n);
}