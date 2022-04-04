#include "../include/w_library.hpp"

int	server_data::_get_index(int clientfd){
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(TMPINDEX);
		tab_request[clientfd].ressource = _link_root_init(ROOT, tab_request[clientfd].ressource);
		if (_set_file(clientfd))
			return (_get_error_404(clientfd));
		return (0);
	}
	return (_send(clientfd, 200));
}

int	server_data::_get(int clientfd){
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _link_root_init(ROOT, tab_request[clientfd].ressource);
		if (_set_file(clientfd))
			return (_get_error_404(clientfd));
		return (0);
	}
	return (_send(clientfd, 200));
}

int	server_data::_get_error(int clientfd){
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].r_buffer.clear();
		if (tab_request[clientfd].return_error == 404)
			tab_request[clientfd].ressource = _data_init(ERRORFILE_404);
		else if (tab_request[clientfd].return_error == 301)
			tab_request[clientfd].ressource = _data_init(ERRORFILE_301);
		else if (tab_request[clientfd].return_error == 408)
			tab_request[clientfd].ressource = _data_init(ERRORFILE_408);
		else
		{
			tab_request[clientfd].return_error = 400;
			tab_request[clientfd].ressource = _data_init(ERRORFILE_400);
		}
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR", 1));
		return (0);
	}
	return (_send(clientfd, tab_request[clientfd].return_error));
}

int	server_data::_get_error_400(int clientfd){
	// std::cout << ERRORFILE_400 << " est l'endroit ou jvais chercher lindex\n";
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(ERRORFILE_400);
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR 400", 1));
		return (0);
	}
	return (_send(clientfd, 400));
}

int	server_data::_get_error_404(int clientfd){
	// std::cout << ERRORFILE_404 << " est l'endroit ou jvais chercher lindex\n";
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(ERRORFILE_404);
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR 404", 1));
		return (0);
	}
	return (_send(clientfd, 404));
}

int	server_data::_get_error_408(int clientfd){
	// std::cout << ERRORFILE_404 << " est l'endroit ou jvais chercher lindex\n";
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(ERRORFILE_408);
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR 404", 1));
		return (0);
	}
	return (_send(clientfd, 404));
}
