#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#include <iostream>
#include <string>
#include <fstream>

#define SERVER_PORT 80

#define MAXLINE 4096
#define SA struct sockaddr
#define SA_IN struct sockaddr_in

// void	err_n_die(const char *fmt, ...){
// 	int			errno_save;
// 	va_list		ap;

// 	errno_save = errno;
// }

int	print_return(std::string ptr, int value)
{
	std::cerr << ptr << std::endl;
	return (value);
}

int	main(int argc, char **argv)
{
	int	sockfd, sendbytes;
	ssize_t n;
	SA_IN servaddr;
	std::string	sendline;
	char	recvline[MAXLINE];

	if (argc != 2)
		return (print_return("Need only one argument", 1));
	//AF : Address Family, INET : internet
	//SOCK_STREAM : Stream Socket
	//0 : Protocol par default, TCP
	// on definit notre servaddr, htons permet de traduir
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (print_return("Error: Socket can't be initialised", 1));
	servaddr.sin_family = AF_INET;
	//htons : host to network, short
	servaddr.sin_port = htons(SERVER_PORT);
	// Traduit en binaire notre adress
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		return (print_return("Traduction inet_pton error ", 1));
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)))
		return (print_return("Connect Failed !", 1));
	sendline = "GET / HTTP/1.1\r\n\r\n";
	sendbytes = sendline.size();
	if (write(sockfd, sendline.c_str(), sendbytes) != sendbytes)
		return (print_return("write error", 1));
	while ((n = recv(sockfd, recvline, MAXLINE, 0)))
		std::cout << recvline << std::endl;
	if (n < 0)
		return (print_return("recv Failed !", 1));
	return (0);
}