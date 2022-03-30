#include "../include/w_library.hpp"

// Je peux en accept plusieurs potentiellement, mais ca me sonne complique
int	server_data::_new_client(std::vector<struct pollfd>::iterator it){
	int	clientfd = accept(serverfd, (SA*) NULL, NULL);

	// std::cout << "Connection Cree pour le fd " << clientfd << " !\n";
	if (clientfd < 0)
		return (print_return("Error: accept", 1));	
	client_poll.fd = clientfd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	tab_poll.insert(tab_poll.end() , client_poll);
	return (0);
	(void)it;
}
int	server_data::handle_line_request(std::vector<struct pollfd>::iterator it, size_t n){
	size_t	i = 0, step3 = 0;
	int	step = 0;

	if (!tab_request[it->fd].parse_data.size())
	{
		for(; i < n && (recvline[i] == '\n' || recvline[i] == '\r'); i++)
			;
		if (i == n)
			return (1);
	}
	tab_request[it->fd].parse_data.insert(tab_request[it->fd].parse_data.end(), recvline.begin().base() + i, recvline.begin().base() + n);
	if (tab_request[it->fd].r_l_v)
		return (0);
	for (i = 0; i < tab_request[it->fd].parse_data.size() && tab_request[it->fd].parse_data[i] != '\n'; i++)
	{
		if (!step && (tab_request[it->fd].parse_data[i] < 'A' || tab_request[it->fd].parse_data[i] > 'Z') && (!i || tab_request[it->fd].parse_data[i] != ' '))
			return (tab_request[it->fd].fill_request(400));
		if (step == 1)
		{
			tab_request[it->fd].ressource.assign(tab_request[it->fd].parse_data.begin() + i, tab_request[it->fd].parse_data.end());
			tab_request[it->fd].clear_ressource();
			tab_request[it->fd].ressource.clear();
			if (tab_request[it->fd].parse_data[i] != '/' || tab_request[it->fd].return_error)
				return (tab_request[it->fd].fill_request(400));
			step++;
		}
		if (step == 3 && !step3)
			step3 = i;
		if (tab_request[it->fd].parse_data[i] == ' ')
		{
			for (;i < tab_request[it->fd].parse_data.size() && tab_request[it->fd].parse_data[i] == ' '; i++)
				;
			i--;
			if (i < tab_request[it->fd].parse_data.size())
				step++;
		}
	}
	if (i == tab_request[it->fd].parse_data.size() || tab_request[it->fd].parse_data[i] != '\n')
		return (0);
	if (step != 3)
		return (tab_request[it->fd].fill_request(400));
	tab_request[it->fd].tmp_data.assign(tab_request[it->fd].parse_data.begin() + step3, tab_request[it->fd].parse_data.begin() + i - 1);
	// tab_request[it->fd].tmp_data.push_back('\0');
	if (tab_request[it->fd].tmp_data != _data_init("HTTP/1.1") && tab_request[it->fd].tmp_data != _data_init("HTTP/1.0"))
		return (tab_request[it->fd].fill_request(400));
	tab_request[it->fd].r_l_v = true;
	tab_request[it->fd].tmp_data.clear();
	return (0);
}

int	server_data::_read_client(std::vector<struct pollfd>::iterator it)
{
	int		n;

	recvline.clear();
	if ((n = recv(it->fd, recvline.begin().base(), MAXLINE, 0)) > 0)
		handle_line_request(it, n);
	if (n < 0)
		return (print_return("Error: recv", 1));
	if (tab_request[it->fd].is_ready())
	{
		if (!tab_request[it->fd].request_ready())
			return (-10);
	}
	return(0);
}

int	server_data::_server_read(std::vector<struct pollfd>::iterator it)
{
	if (it->fd == serverfd)
		return (_new_client(it));
	return (_read_client(it));
}

