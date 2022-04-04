#include "../include/w_library.hpp"

int		RP15::_post_cgi(server_data *d_s, int clientfd){
	if (responding < 2)
	{
		int fd;

		ressource = _data_init(FILE_CGI);
		ressource.push_back('\0');
		fd = open((char*)ressource.begin().base(), O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (print_return("FILE_CGI pas dispo !", -10));
		ressource.pop_back();
		basic_cgi(d_s, fd);
		if (d_s->_set_file(clientfd))
			return (d_s->_get_error_404(clientfd));
		return (0);
	}
	return (d_s->_send(clientfd, 200));
}
