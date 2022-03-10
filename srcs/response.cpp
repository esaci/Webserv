#include "../include/w_library.hpp"

int	_response(DATA tmp, DATA tmp2, int clientfd)
{
	std::string tmps;
	DATA	buff;
	int		n;

	(void)tmp;
	(void)tmp2;
	tmps = "HTTP/1.0 200 OK\r\n\r\nHello";
	buff.assign(tmps.begin(), tmps.end());
	n = write(clientfd, buff.begin().base(), buff.size());
	return (n);
}