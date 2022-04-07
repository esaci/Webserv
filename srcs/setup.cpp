#include "../include/w_library.hpp"
#include <stdio.h>
#include <errno.h>

int		server_data::setup_listen(std::vector<struct pollfd>::iterator it){
	if (!(it < tab_poll.end()))
		return (0);
	if (!tab_ap.size() && it->revents && !(it->revents & POLLIN) && !(it->revents & POLLOUT))
		return (print_return("Revents chelou\n\n\n", 1));
	if (!tab_ap.size())
		return (0);
	if (sockets_to_hosts.find(it->fd) == sockets_to_hosts.end())
		return (0);
	if (tab_ap.find(sockets_to_hosts.find(it->fd)->second) == tab_ap.end())
		return (0);
	if ((listen(sockets_to_hosts.find(it->fd)->first, NBRCLIENTMAX)) < 0)
			return (print_return("Error: Listen", 1));
	tab_ap.erase(sockets_to_hosts.find(it->fd)->second);
	return (0);
}

int		server_data::setup_read(std::vector<struct pollfd>::iterator it){
	int n = 0;
	
	if (!(it < tab_poll.end()) || !(it->revents & POLLIN) || tab_request[it->fd].responding || files_to_clients[it->fd])
		return (0);
	if (tab_request[it->fd].method == _data_init("POST"))
		n = _post_server_read(it);
	else
		n = _server_read(it);
	if (n == -10)
	{
		it->events = POLLOUT;
		if (!tab_request[it->fd].host.size() && tab_request[it->fd].protocol == _data_init("HTTP/1.1"))
			tab_request[it->fd].fill_request(400, it);
	}
	else if (n)
		return(1);
	return(0);
}

int		server_data::setup_response(std::vector<struct pollfd>::iterator it){
	int n;
	
	if (!(it < tab_poll.end()) || !(it->revents & POLLOUT) || files_to_clients[it->fd])
		return (0);
	n = _response(it->fd);
	if (n == -10)
	{
		tab_request.erase(it->fd);
		close(it->fd);
		tab_poll.erase(it);
		pos--;
	}
	else if (n)
		return (1);
	return (0);
}

int		server_data::setup_read_files(std::vector<struct pollfd>::iterator it){
	int n;

	if (it >= tab_poll.end() || !(it->revents & POLLIN) || !files_to_clients[it->fd] || tab_request[files_to_clients[it->fd]].responding != 2)
		return (0);
	// if (!tab_request[files_to_clients[it->fd]].return_error)
	// {
	recvline.clear();
	if ( (n = read(it->fd, recvline.begin().base(), MAXLINE - 1)) > 0 )
		tab_request[files_to_clients[it->fd]].r_buffer.insert(tab_request[files_to_clients[it->fd]].r_buffer.end(), recvline.begin().base(), recvline.begin().base() + n);
	if (n < 0)
		return (print_return("ERROR: READ_FILE", 1));
	if (n <= (MAXLINE - 1))
	{
		recvline.clear();
		if (read(it->fd, recvline.begin().base(), 1))
		{
			tab_request[files_to_clients[it->fd]].r_buffer.insert(tab_request[files_to_clients[it->fd]].r_buffer.end(), recvline.begin().base(), recvline.begin().base() + 1);
			return (0);

		}
		tab_request[files_to_clients[it->fd]].responding = 3;
		files_to_clients[it->fd] = 0;
		close(it->fd);
		tab_request.erase(it->fd);
		tab_poll.erase(it);
		pos--;
	}
	// }
	return (0);
}