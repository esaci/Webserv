#include "../include/w_library.hpp"


int	init_socket( void ){
	SA_IN		servaddr;
	int			on = 1;
	int			serverfd;

	if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		print_return("Error: Socket", 1);

	// Permet au sd(socket descriptor) d'etre reutilisable
	// SOL_SOCKET : La couche vise est celle qui ne depend pas du protocole
	// SO_REUSADDR : Option a ajouter a ma socket, ici le fait qu'elle soit reutilisable
	// 3e argument sert a acceder a l'option precise, 1 ici (Aucune idee de pk 1)
	if ( (setsockopt(serverfd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on))) < 0)
			return (print_return("ERROR: Setsockopt", 1));
	servaddr.sin_family = AF_INET;
	//Prend n'importe quel adress
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//Port 18000 pour eviter le port 80 et ainsi ne pas avoir de soucis
	servaddr.sin_port = htons(SERVER_PORT);
	
	// Bind la socket a l'adress 
	if ((bind(serverfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
		print_return("Error: Bind", 1);
	// On donne ensuite l'ordre qu'on le listen
	if ((listen(serverfd, 10)) < 0)
		print_return("Error: Listen", 1);
	return (serverfd);
}

int	server_data::_server( void )
{
	int							serverfd, clientfd, n;
	uint8_t						recvline[MAXLINE + 1];
	struct pollfd				client_poll;
	std::vector<struct pollfd>	tab_client;
	std::vector<SA_IN>			tmp;
	socklen_t					tmplen;
	
	serverfd = init_socket();
	while (1){
		std::cout << "Waiting for a connection on Port " << SERVER_PORT << "\n Actuellement " << tab_client.size() << " clients" << std::endl;
		// accept va attendre que quelquun se connect
		
		tmplen = sizeof(tmp.begin().base());
		SA_IN test;
		tmp.push_back(test);
		clientfd = accept(serverfd, (SA*)&tmp.begin().base(), &(tmplen));
		std::cout << "On a " << tmp.size() << " connections actuellement\n";
		for(std::vector<SA_IN>::iterator it = tmp.begin(); it < tmp.end(); it++)
		{
			std::cout << "Info sur la connection :\n";
			std::cout << it->sin_family << " est la sa_family\n";
			std::cout << it->sin_addr.s_addr << " est la data\n";
			std::cout << it->sin_port << " est le port\n";
		}
		if ( fcntl(clientfd, F_SETFL, O_NONBLOCK) < 0 )
			return (print_return("ERROR: fcntl", 1));
		client_poll.fd = clientfd;
		client_poll.events = POLLIN;
		client_poll.revents = 0;
		tab_client.push_back(client_poll);
		std::cout << "ca bloque la\n";
		if ( !(n = poll(tab_client.begin().base(), tab_client.size(), 10)) )
		{
			print_return("TIMEOUT: poll", 1);
		}
		if (n < 0)
		{
			print_return("ERROR: poll", 1);
			break;
		}
		std::cout << "pk\n";
		for (std::vector<struct pollfd>::iterator it = tab_client.begin(); it < tab_client.end(); it++, clientfd = it->fd)
		{
			if (it->revents == POLLIN)
			{
				DATA parse_data;
				std::cout << "ca bloque ici\n";
				while ((n = recv(clientfd, recvline, MAXLINE, 0)) > 0)
				{
					parse_data.insert(parse_data.end(), recvline, recvline + n);
					if (recvline[n - 1] == '\n'){
						break ;
					}
				}
				if (n < 0)
					return (print_return("Error: recv", 1));
				if (parse_data.size())
				{
					R_DATA p(parse_data);
					p.display_cpcr();
					_response(p, clientfd);
					tab_client.erase(it);
					close(clientfd);
				}
			}
		}
		std::cout << "sheesh\n";
	}
	for (std::vector<struct pollfd>::iterator it = tab_client.begin(); it < tab_client.end(); it++, clientfd = it->fd)
		close(clientfd);
	close(serverfd);
	return (0);
}