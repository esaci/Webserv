#include "../include/w_library.hpp"


int	init_socket( void ){
	SA_IN		servaddr;
	int			on = 1;
	int			serverfd;

	if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		print_return("Error: Socket", -2);

	// Permet au sd(socket descriptor) d'etre reutilisable
	// SOL_SOCKET : La couche vise est celle qui ne depend pas du protocole
	// SO_REUSADDR : Option a ajouter a ma socket, ici le fait qu'elle soit reutilisable
	// 3e argument sert a acceder a l'option precise, 1 ici (Aucune idee de pk 1)
	if ( (setsockopt(serverfd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on))) < 0)
			return (print_return("ERROR: Setsockopt", -1));
	servaddr.sin_family = AF_INET;
	//Prend n'importe quel adress
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);
	if ((bind(serverfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
		print_return("Error: Bind", -1);
	return (serverfd);
}

//FAUDRA METTRE LE COMPORTEMENT AVEC POLLOUT
int	server_data::_server( void ){
	int		n;
	size_t	pos, len;
	// int	fd = open(TMPFAVICO, O_RDONLY);
	serverfd = init_socket();
	if (serverfd < 0)
		return (1);
	_table_poll_init();
		std::cout << "Waiting for a connection on Port " << SERVER_PORT << "\n" << std::endl;
	while (1){
		len = tab_poll.size();
		
		// std::cout <<"Actuellement " << len - 1 << " client(s)" << std::endl;
		// if (listening)
		// {
			// client_poll.fd = fd;
			// client_poll.events = POLLIN;
			// client_poll.revents = 0;
			// tab_poll.push_back(client_poll);
		// }
		if ( !(n = poll(tab_poll.begin().base(), tab_poll.size(), TIMEOUT)) )
			return (print_return("TIMEOUT: poll", 1));
		if (n < 0)
			return (print_return("ERROR: poll", 1));
		pos = 0;
		for (std::vector<struct pollfd>::iterator it = tab_poll.begin(); it < tab_poll.end() && pos < len; ++pos, it = tab_poll.begin() + pos)
		{
			// if (listening && it->fd == fd && it->revents & POLLIN)
			// {
				// std::cerr << "CA FONCTIONNE \n\n";
				// continue;
			// }
			if (listening && it->revents && !(it->revents & POLLIN) && !(it->revents & POLLOUT))
				return (print_return("Revents chelou\n\n\n", 1));
			if (setup_listening(it->fd))
				return (1);
			n = 0;
			if (it->revents & POLLIN)
				n = _server_read(it);
			if (n == -10)
				it->events = POLLOUT;
			else if (n)
				break ;
			n = 0;
			if (it->revents & POLLOUT)
				n = _response(it->fd);
			if (n == -10)
			{
				std::cout << "Connection " << it->fd << " Closed !\n";
				tab_request.erase(it->fd);
				close(it->fd);
				tab_poll.erase(it);
				pos--;
			}	
		}
	}
	return (0);
}