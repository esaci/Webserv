#include "../include/w_library.hpp"

int		server_data::setup_listen(std::vector<struct pollfd>::iterator it){
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
	
	if ((it->revents & POLLOUT) && !files_to_socket[it->fd])
		n = _response(it->fd);
	if (n == -10)
	{
		std::cout << "Connection " << it->fd << " Closed !\n";
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
	if ((it->revents & POLLIN) && files_to_socket[it->fd] && tab_request[files_to_socket[it->fd]].responding == 2)
	{
		std::cout << "Ca va lire le " << it->fd << " fd \n";
		recvline.clear();
		int n;
		if ( (n = recv(it->fd, recvline.begin().base(), MAXLINE - 1, 0)) > 0 )
			tab_request[files_to_socket[it->fd]].r_buffer.insert(tab_request[files_to_socket[it->fd]].r_buffer.end(), recvline.begin().base(), recvline.begin().base() + n);
		if (n < 0)
			return (print_return("ERROR: READ_FILE", 1));
		if (n < (MAXLINE - 1))
		{
			recvline.clear();
			if (recv(it->fd, recvline.begin().base(), 1, 0))
			{
				tab_request[files_to_socket[it->fd]].r_buffer.insert(tab_request[files_to_socket[it->fd]].r_buffer.end(), recvline.begin().base(), recvline.begin().base() + 1);
				return (0);
			}
			tab_request[files_to_socket[it->fd]].responding = 3;
			close(it->fd);
			tab_poll.erase(it);
			pos--;
			files_to_socket[it->fd] = 0;
		}
	}
	return (0);
}