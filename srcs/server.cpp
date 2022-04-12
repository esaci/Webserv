#include "../include/w_library.hpp"


int	init_socket(std::set<A_P > &tab_ap, std::map<int, A_P> &sockets_to_hosts){
	SA_IN		servaddr;
	int			on = 1;
	int			serverfd;

	for(std::set<A_P >::iterator it = tab_ap.begin(); it != tab_ap.end(); it++)
	{
		if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			print_return("Error: Socket", 1);
		// Permet au sd(socket descriptor) d'etre reutilisable
		// SOL_SOCKET : La couche vise est celle qui ne depend pas du protocole
		// SO_REUSADDR : Option a ajouter a ma socket, ici le fait qu'elle soit reutilisable
		// 3e argument sert a acceder a l'option precise, 1 ici (Aucune idee de pk 1)
		if ( (setsockopt(serverfd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on))) < 0)
				return (print_return("ERROR: Setsockopt", 1));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = inet_addr(it->first.c_str());
		servaddr.sin_port = htons(it->second);
		if ((bind(serverfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
			print_return("Error: Bind", 1);
		sockets_to_hosts[serverfd] = *it;
	}
	return (0);
}

int	server_data::_server( void ){
	int		n;
	size_t	len;
	int		flag_socket;
	
	flag_socket = init_socket(tab_ap, sockets_to_hosts);
	if (flag_socket)
		return (1);
	_table_poll_init();
	for(std::set<A_P >::iterator it = tab_ap.begin(); it != tab_ap.end(); it++)
		std::cout << "Waiting for a connection on Port " << it->first << ":" << it->second << std::endl;
	while (1){
		_time_maj();
		len = tab_poll.size();
		pos = 0;
		if ( !(n = poll(tab_poll.begin().base(), tab_poll.size(), TIMEOUT)) )
			return (print_return("TIMEOUT: poll", 1));
		// std::cout << "On a " << len << " Clients connectes !\n";
		if (n < 0)
			return (print_return("ERROR: poll", 1));
		for (std::vector<struct pollfd>::iterator it = tab_poll.begin(); it < tab_poll.end() && pos < len; ++pos, it = tab_poll.begin() + pos)
		{
			if (setup_listen(tab_poll.begin() + pos))
				return (print_return("SOUCIS VIENT DE setup_listen ",1));
			if (setup_response(tab_poll.begin() + pos))
				return (print_return("SOUCIS VIENT DE setup_response ",1));
			if (setup_read(tab_poll.begin() + pos))
				break ;
			if (setup_read_files(tab_poll.begin() + pos))
				return (print_return("SOUCIS VIENT DE read_files ",1));			
			if (setup_write_files(tab_poll.begin() + pos))
				return (print_return("SOUCIS VIENT DE write_files", 1));
		}
	}
	return (0);
}