#include "../include/w_library.hpp"

int		RP15::_post_cgi(server_data *d_s, int clientfd){
	if (responding < 2)
	{
		int fd;

		fd = open(FILE_CGI, O_RDWR | O_CREAT | O_TRUNC, 0666);
		d_s->files_to_clients[fd] = clientfd;
		if (fd < 0)
			return (print_return("FILE_CGI pas dispo !", -10));
		basic_cgi(d_s, fd);
		ressource = _data_init(FILE_CGI);
		if (d_s->_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER FILE_CGI 400", 1));
		return (0);
	}
	return (d_s->_send(clientfd, 200));
}
