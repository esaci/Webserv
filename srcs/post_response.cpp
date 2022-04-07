#include "../include/w_library.hpp"
// 
int		RP15::_post_cgi(server_data *d_s, int clientfd){
	if (responding < 2)
	{
		DATA	temp;
		int fd;
		if (method == _data_init("GET"))
		{
			DATA::iterator it;
			for (it = ressource.begin(); it < ressource.end() && *it != '?'; it++)
				;
			// faire ++it si it != ressource.end(), pour ne pas avoir ?, OSCAR
			r_body_get.assign(it, ressource.end());
			ressource.erase(it, ressource.end());
			std::cout << ressource << std::endl;
		}
		temp = _data_init(FILE_CGI);
		temp.push_back('\0');
		fd = open((char*)temp.begin().base(), O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (print_return("FILE_CGI pas dispo !", -10));
		basic_cgi(d_s, fd);
		if (d_s->_set_file(clientfd))
			return (d_s->_get_error_404(clientfd));
		return (0);
	}
	return (d_s->_send(clientfd, 200));
}


int	server_data::_post_upload(int clientfd)
{
	(void)clientfd;
	// TOUTE LES INFOS DU CLIENT SONT SUR tab_request[clientfd]
	// Pour avoir ladresse et le port du client, sockets_to_hosts[clientfd]
	// if (responding < 2)
	// {
// 
	// }
	return (_send(clientfd, 200));
}