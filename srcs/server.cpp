#include "../include/w_library.hpp"

int	print_return(std::string ptr, int value)
{
	std::cerr << ptr << std::endl;
	return (value);
}

std::string bin2hex(const unsigned char *input, size_t len){
	std::string hexits = "0123456789ABCDEF";
	int		resultlength = (len * 3) + 1;
	std::string result(resultlength, '\0');

	if (input == NULL || len <= 0)
		return NULL;

	for (size_t i = 0; i < len; i++){
		result[i * 3] = hexits[input[i] >> 4];
		result[(i * 3) + 1] = hexits[input[i] >> 0x0F];
		result[(1 * 3) + 2] = ' ';
	}

	return (result);
}

// int	main(int argc, char **argv)
int	_server( void )
{
	struct pollfd var_poll;
	int			serverfd, clientfd, n;
	SA_IN		servaddr;
	std::vector<unsigned char>	buff;
	uint8_t		recvline[MAXLINE + 1];
	int			tmp;
	std::string	tmps;
	struct pollfd client_poll;
	std::vector<struct pollfd> tab_client;
	// SA_IN addr;
	// socklen_t addr_len;


	if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		print_return("Error: Socket", 1);

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
	while(1){
		std::cout << "Waiting for a connection on Port " << SERVER_PORT << std::endl;
		// accept va attendre que quelquun se connect
		clientfd = accept(serverfd, (SA *) NULL, NULL);
		client_poll.fd = clientfd;
		client_poll.events = POLLIN;
		client_poll.revents = 0;
		tab_client.push_back(client_poll);
		if ( !(tmp = poll(tab_client.begin().base(), tab_client.size(), 30000)) )
		{
			print_return("TIMEOUT: poll", 1);
			break;
		}
		if (tmp < 0)
		{
			print_return("ERROR: poll", 1);
			break;
		}
		for (std::vector<struct pollfd>::iterator it = tab_client.begin(); it < tab_client.end(); it++, clientfd = it->fd)
		{
			while ((n = recv(clientfd, recvline, MAXLINE, 0)) > 0)
			{
					std::cout << bin2hex(recvline, n) << " " << recvline << std::endl;
					if (recvline[n - 1] == '\n'){
						break;
					}
			}
			if (n < 0)
				print_return("Error: recv", 1);
		}
		tmps = "HTTP/1.0 200 OK\r\n\r\nHello";
		buff.assign(tmps.begin(), tmps.end());
		write(clientfd, buff.begin().base(), buff.size());
		close(clientfd);
	}
	(void)var_poll;
	return (0);
}