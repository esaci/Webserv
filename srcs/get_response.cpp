#include "../include/w_library.hpp"

int	server_data::_get_index(int clientfd){
	std::string root;

	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource.push_back('\0');
		root = serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_root((char*)tab_request[clientfd].u_ressource.begin().base());
		tab_request[clientfd].ressource = _data_init(serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_all_index((char*)tab_request[clientfd].u_ressource.begin().base())[0]);
		tab_request[clientfd].ressource = _link_root_init(root, tab_request[clientfd].ressource);
		if (_set_file(clientfd))
			return (_get_error_404(clientfd));
		return (0);
	}
	return (_send(clientfd, 200));
}

int	server_data::_get(int clientfd){
	std::string root;

	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource.push_back('\0');
		root = serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_root((char*)tab_request[clientfd].u_ressource.begin().base());
		_erase_location(tab_request[clientfd].ressource, serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).map_root, root);
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
		if (tab_request[clientfd].return_error)
			tab_request[clientfd].ressource = _data_init(serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_error_page((char*)tab_request[clientfd].u_ressource.begin().base(), tab_request[clientfd].return_error));
		else
		{
			tab_request[clientfd].return_error = 400;
			tab_request[clientfd].ressource = _data_init(serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_error_page((char*)tab_request[clientfd].u_ressource.begin().base(), 400));
		}
		if (tab_request[clientfd].return_error < 0)
			tab_request[clientfd].return_error = 200;
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR", 1));
		return (0);
	}
	return (_send(clientfd, tab_request[clientfd].return_error));
}

int	server_data::_get_error_400(int clientfd){
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_error_page((char*)tab_request[clientfd].u_ressource.begin().base(), 400));
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR 400", 1));
		return (0);
	}
	return (_send(clientfd, 400));
}

int	server_data::_get_error_404(int clientfd){
	if (tab_request[clientfd].return_error == 400)
		return (_get_error_400(clientfd));
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_error_page((char*)tab_request[clientfd].u_ressource.begin().base(), 404));
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR 404", 1));
		return (0);
	}
	return (_send(clientfd, 404));
}

int	server_data::_get_error_403(int clientfd){
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_error_page((char*)tab_request[clientfd].u_ressource.begin().base(), 403));
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR 403", 1));
		return (0);
	}
	return (_send(clientfd, 403));
}

int	server_data::_get_error_408(int clientfd){
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_error_page((char*)tab_request[clientfd].u_ressource.begin().base(), 408));
		if (_set_file(clientfd))
			return (print_return("ERROR OPEN DU FICHIER _GET_ERROR 404", 1));
		return (0);
	}
	return (_send(clientfd, 408));
}
