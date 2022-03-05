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

	for (int i = 0; i < len; i++){
		result[i * 3] = hexits[input[i] >> 4];
		result[(i * 3) + 1] = hexits[input[i] >> 0x0F];
		result[(1 * 3) + 2] = ' ';
	}

	return (result);
}

int	main(int argc, char **argv)
{
	int			listenfd, connfd, n;
	SA_IN		servaddr;
	std::string	buff;
	uint8_t		recvline[MAXLINE + 1];

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		print_return("Error: Socket", 1);

	servaddr.sin_family = AF_INET;
	//Prend n'importe quel adress
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//Port 18000 pour eviter le port 80 et ainsi ne pas avoir de soucis
	servaddr.sin_port = htons(SERVER_PORT);
	
	// Bind la socket a l'adress 
	if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
		print_return("Error: Bind", 1);
	// On donne ensuite l'ordre qu'on le listen
	if ((listen(listenfd, 10)) < 0)
		print_return("Error: Listen", 1);
	while(1){
		SA_IN addr;
		socklen_t addr_len;

		std::cout << "Waiting for a connection on Port " << SERVER_PORT << std::endl;
		std::cout.flush();
		// accept va attendre que quelquun se connect
		connfd = accept(listenfd, (SA *) NULL, NULL);
		while ((n = recv(connfd, recvline, MAXLINE, 0)) > 0)
		{
				std::cout << bin2hex(recvline, n) << " " << recvline << std::endl;
				if (recvline[n - 1] == '\n'){
					break;
				}
		}
		if (n < 0)
			print_return("Error: recv", 1);
		buff = "HTTP/1.0 200 OK\r\n\r\nHello";
		write(connfd, buff.c_str(), buff.size());
		close(connfd);
	}
	return (0);
}