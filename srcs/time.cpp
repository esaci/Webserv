#include "../include/w_library.hpp"


int		RP15::_time_init( void ){
	char buf[200];
	
	time_client = std::time(0);
	std::tm* now = std::localtime(&time_client);
	strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", now);
	// std::cout << "La request a ete lance a " << buf << std::endl;
	return (0);
}

int			server_data::_time_stop_client(std::vector<struct pollfd>::iterator it)
{
	if (tab_request[it->fd].return_error || (files_to_clients[it->fd] && tab_request[files_to_clients[it->fd]].return_error))
		return (0);
	if (files_to_clients[it->fd])
	{
		close(it->fd);
		std::cout << "TIMEOUT DE LECTURE D'UN FICHIER " << it->fd << "\n";
		tab_request.erase(it->fd);
		tab_poll.erase(it);
		files_to_clients[it->fd] = 0;
		it->fd = files_to_clients[it->fd];
	}
	tab_request[it->fd]._time_init();
	tab_request[it->fd].return_error = 408;
	// tab_request[it->fd].ressource = _data_init(ERRORFILE_408);
	tab_request[it->fd].responding = 1;
	tab_request[it->fd].r_buffer.clear();
	std::cout << "TIMEOUT D'UN CLIENT, Il va recevoir 408\n";
	return (0);
}

int		server_data::_time_maj( void )
{
	char	buf[200];
	double	diff_time = 0;
	size_t	i = 0;

	time_server = std::time(0);
	std::tm* now = std::localtime(&time_server);
	strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", now);
	// std::cout << "Le temps de server est " << buf << std::endl;	
	// if (tab_request.size())
		// std::cout << "On a donc une diff time de :\n";
	for (std::vector<struct pollfd>::iterator it = tab_poll.begin(); it < tab_poll.end() && i < tab_poll.size(); ++i, it = tab_poll.begin() + i)
	{
		if (it->fd == serverfd)
			continue ;
		diff_time = difftime(time_server, tab_request[it->fd].time_client);
		// std::cout << "Client " << i << " existe depuis " << diff_time << " sa ressource est " << tab_request[it->fd].ressource << std::endl;
		if (diff_time > TIMEOUT_CLIENT)
			i += _time_stop_client(tab_poll.begin() + i);
	}
	return (0);
}