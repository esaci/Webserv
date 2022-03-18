#include "../include/w_library.hpp"

int	server_data::_server_read(std::vector<struct pollfd>::iterator it)
{
	if (it->fd == serverfd)
		return (_new_client(it));
	return (_read_client(it));
}
// Je peux en accept plusieurs potentiellement, mais ca me sonne complique
int	server_data::_new_client(std::vector<struct pollfd>::iterator it){
	int	clientfd = accept(serverfd, (SA*) NULL, NULL);

	std::cout << "Connection Cree pour le fd " << clientfd << " !\n";
	if (clientfd < 0)
		return (print_return("Error: accept", 1));
	
	struct pollfd	client_poll;
	
	client_poll.fd = clientfd;
	client_poll.events = POLLIN | POLLOUT;
	client_poll.revents = 0;
	tab_poll.insert(tab_poll.end() , client_poll);
	return (0);
	(void)it;
}

// Pour linstant je met un gros read, mais il va falloir faire en sorte que lorsque ca read pas jusqua double \r\n\r\n
// ca stock juste/ajoute dans le vector de la class
int	server_data::_read_client(std::vector<struct pollfd>::iterator it)
{
	int							n;
	
	parse_temp.clear();
	recvline.clear();
	if ((n = recv(it->fd, recvline.begin().base(), MAXLINE, 0)) > 0)
		parse_temp.assign(recvline.begin().base(), recvline.begin().base() + n);
	if (n < 0)
		return (print_return("Error: recv", 1));
	if (parse_temp.size())
	{
		tab_request[it->fd].insert(parse_temp);
		// tab_request[it->fd].display_cpcr();
		if (tab_request[it->fd].is_ready())
		{
			tab_request[it->fd].request_ready();
			_response(it->fd);
			tab_request.erase(it->fd);
			return (-10);
		}
	}
	return(0);
}