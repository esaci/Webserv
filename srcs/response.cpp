#include "../include/w_library.hpp"

int	_response(DATA tmp, DATA tmp2, int clientfd)
{
	std::string tmps;
	DATA	buff, tmpb;
	int		n;
	char		recvline[MAXLINE + 1];

	// (void)tmp;
	(void)tmp2;
	tmps = "GET";
	tmpb.assign(tmps.begin(), tmps.end());
	tmps = "HTTP/1.0 200 OK\r\n\r\n";
	buff.assign(tmps.begin(), tmps.end());
	if (tmp == tmpb)
	{
		// std::cout << "CA PASSE VERS LE IF\n\n";
		std::fstream fs;
		fs.open(TMPINDEX, std::fstream::in);
		if (!fs)
			print_return("ERROR READ DU FICHIER", 1);
		// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
		fs.read(recvline, MAXLINE);
		while (fs.gcount()){
			buff.insert(buff.end(), recvline, recvline + fs.gcount());
			fs.read(recvline, MAXLINE);
		}
		// n = write(0, buff.begin().base(), buff.size());
		n = write(clientfd, buff.begin().base(), buff.size());
		return (n);
	}
	tmps = "HTTP/1.0 200 OK\r\n\r\nHello";
	buff.assign(tmps.begin(), tmps.end());
	n = write(clientfd, buff.begin().base(), buff.size());
	return (n);
}