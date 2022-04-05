#include "../include/w_library.hpp"


int		RP15::_time_init( void ){
	time_client = std::time(0);
	return (0);
}

int			server_data::_time_stop_client(std::vector<struct pollfd>::iterator it)
{
	if (tab_request[it->fd].return_error)
		return (0);
	size_t	fd = it->fd;
	int		i = 0;
	if (files_to_clients[it->fd])
	{
		fd = files_to_clients[it->fd];
		files_to_clients[it->fd] = 0;
		close(it->fd);
		tab_request.erase(it->fd);
		tab_poll.erase(it);
		tab_request[fd].responding = 1;
		tab_request[fd].fill_request(408);
		i = -1;
	}
	if (tab_request[fd].responding >= 3 || !tab_request[fd].responding)
	{
		tab_request[fd].responding = 1;
		tab_request[fd].fill_request(408);
	}
	return (print_return("TIMEOUT D'UN CLIENT, Il va recevoir 408", i));
}

int		server_data::_time_maj( void )
{
	double	diff_time = 0;
	size_t	i = 0, j = 0;
	static size_t c = tab_poll.size();

	time_server = std::time(0);
	for (std::vector<struct pollfd>::iterator it = tab_poll.begin(); it < tab_poll.end() && i < tab_poll.size(); ++i, it = tab_poll.begin() + i)
	{
		if (it->fd == serverfd)
			continue ;
		diff_time = difftime(time_server, tab_request[it->fd].time_client);
		if (diff_time > TIMEOUT_CLIENT)
		{
			if (j < (diff_time - TIMEOUT_CLIENT))
				j = (diff_time - TIMEOUT_CLIENT);
			i += _time_stop_client(tab_poll.begin() + i);
		}
	}
	if (c != tab_poll.size())
		c = tab_poll.size();
	return (0);
}