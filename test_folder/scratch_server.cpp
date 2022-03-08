#include "../include/w_library.hpp"

int	print_return(std::string ptr, int value)
{
	std::cerr << ptr << std::endl;
	return (value);
}

int main( void )
{
	int listenfd;
	int	clientfd;
	SA_IN tmpbind;
	std::vector<struct pollfd> vpollfd;
	struct pollfd tmpoll;
	int	tmp;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0) == -1))
		return (print_return("Error: Socket", 1));
	tmpbind.sin_family = AF_INET;
	tmpbind.sin_port = htons(SERVER_PORT);
	tmpbind.sin_addr.s_addr = htons(INADDR_ANY);
	if (bind(listenfd, (SA*) &tmpbind, sizeof(tmpbind)))
		return (print_return("Error: Bind", 1));
	if (listen(listenfd, 10))
		return (print_return("Error: Listen", 1));
	while(1)
	{
		std::cout << "Ready for client connect() on PORT " << SERVER_PORT << std::endl;
		clientfd = accept(listenfd, (SA*) NULL, 0);
		if (clientfd < 0)
			return (print_return("Error: Accept !?", 1));
		tmpoll.fd = clientfd;
		tmpoll.events = POLLIN;
		tmpoll.revents = 0;
		vpollfd.push_back(tmpoll);
		if ( !(tmp = poll(vpollfd.begin().base(), vpollfd.size(), 30000)) )
		{
			print_return("TIMEOUT: poll", 1);
			break;
		}
		if (tmp < 0)
		{
			print_return("ERROR: poll", 1);
			break;
		}
		tmp = recv()

	}
	return (0);
}