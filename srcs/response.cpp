#include "../include/w_library.hpp"

int	_response(R_DATA p, int clientfd, C_DATA *codes)
{
	DATA	buff, tmpb;
	int		n;
	char		recvline[MAXLINE + 1];

	tmpb = _data_init("GET");
	buff = _data_init("HTTP/1.0 200 OK\r\n\r\n");
	if (p.method == tmpb)
	{
		tmpb = _data_init("/");
		// Il faudra rajouter la condition si on prend en ressource lindex directement
		if (tmpb == p.ressource)
			return (_get_index());
		tmpb = _data_init("/favicon.ico");
		if (tmpb == p.ressource)
			return (_get_favicon());
	}
	buff = _data_init("HTTP/1.0 200 OK\r\n\r\nHello");
	n = write(clientfd, buff.begin().base(), buff.size());
	return (n);
	(void)codes;
}