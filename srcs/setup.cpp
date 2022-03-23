#include "../include/w_library.hpp"
#include <stdio.h>
#include <errno.h>

int		server_data::setup_listen(std::vector<struct pollfd>::iterator it){
	if (!(it < tab_poll.end()))
		return (0);
	if (listening && it->revents && !(it->revents & POLLIN) && !(it->revents & POLLOUT))
		return (print_return("Revents chelou\n\n\n", 1));
	if (!listening && it->fd == serverfd)
	{
		listening = true;
		if ((listen(serverfd, NBRCLIENTMAX)) < 0)
			return (print_return("Error: Listen", 1));
	}
	return (0);
}

int		server_data::setup_read(std::vector<struct pollfd>::iterator it){
	int n = 0;
	
	if (!(it < tab_poll.end()))
		return (0);
	if (it->revents & POLLIN && !files_to_socket[it->fd])
		n = _server_read(it);
	if (n == -10)
		it->events = POLLOUT;
	else if (n)
		return(1);
	return(0);
}

int		server_data::setup_response(std::vector<struct pollfd>::iterator it){
	int n = 0;
	
	if (!(it < tab_poll.end()))
		return (0);
	if ((it->revents & POLLOUT) && !files_to_socket[it->fd])
		n = _response(it->fd);
	if (n == -10)
	{
		// std::cout << "Connection " << it->fd << " Closed !\n";
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
	if (it >= tab_poll.end())
		return (0);
	if (files_to_socket[it->fd] && (it->revents & POLLIN) && tab_request[files_to_socket[it->fd]].responding == 2)
	{
		recvline.clear();
		int n;
		if ( (n = read(it->fd, recvline.begin().base(), MAXLINE - 1)) > 0 )
			tab_request[files_to_socket[it->fd]].r_buffer.insert(tab_request[files_to_socket[it->fd]].r_buffer.end(), recvline.begin().base(), recvline.begin().base() + n);
		if (n < 0)
			return (print_return("ERROR: READ_FILE", 1));
		if (n < (MAXLINE - 1))
		{
			recvline.clear();
			if (read(it->fd, recvline.begin().base(), 1))
			{
				tab_request[files_to_socket[it->fd]].r_buffer.insert(tab_request[files_to_socket[it->fd]].r_buffer.end(), recvline.begin().base(), recvline.begin().base() + 1);
				return (0);
			}
			tab_request[files_to_socket[it->fd]].responding = 3;
			files_to_socket[it->fd] = 0;
			close(it->fd);
			tab_poll.erase(it);
			pos--;
			
		}
	}
	return (0);
}