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
	client_poll.events = POLLIN;
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
	DATA						parse_data;
	uint8_t						recvline[MAXLINE + 1];
	// parse_data.clear();
	std::cout << "Info sur la connection :\n";
	std::cout << it - tab_poll.begin() << " client !\n";
	std::cout << it->fd << " est le fd\n";
	if ((n = recv(it->fd, recvline, MAXLINE, 0)) > 0)
	{
		parse_data.assign(recvline, recvline + n);
		// std::cout << parse_data.begin().base() << " : est la ligne\n";
	}
	if (n < 0)
		return (print_return("Error: recv", 1));
	if (parse_data.size())
	{
		tab_request[it->fd].insert(parse_data);
		// tab_request[it->fd].display_cpcr();
		if (tab_request[it->fd].is_ready())
		{
			tab_request[it->fd].request_ready();
			std::cout << "Considere la lecture est suffisante\n";
			_response(it->fd);
			tab_request.erase(it->fd);
			return (-10);
		}
		std::cout << "Considere la lecture n'est pas suffisante\n";
	}
	return(0);
}