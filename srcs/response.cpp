#include "../include/w_library.hpp"

int	_response(R_DATA p, int clientfd, C_DATA *codes)
{
	DATA	buff, tmpb, tmpb2;
	int		n;

	tmpb = _data_init("GET");
	// buff = _data_init("HTTP/1.0 200 OK\r\n\r\n");
	if (p.method == tmpb)
	{
		tmpb = _data_init("/");
		tmpb2 = _data_init(TMPINDEX);
		// Il faudra rajouter la condition si on prend en ressource lindex directement
		// Faudra ameliorer ce if
		if ((tmpb == p.ressource && tmpb.size() == p.ressource.size()) || tmpb2 == p.ressource)
			return (_get_index(clientfd, codes));
		tmpb = _data_init("/favicon.ico");
		if (tmpb == p.ressource)
			return (_get_favicon(clientfd, codes));
		if (AUTOINDEX)
			return(_get_error_400(clientfd, codes));
		return(_get_error_404(clientfd, codes));
	}
	buff = _data_init("HTTP/1.0 200 OK\r\n\r\nHello");
	n = write(clientfd, buff.begin().base(), buff.size());
	return (n);
	(void)codes;
}