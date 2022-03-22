#include "../include/w_library.hpp"

int	server_data::_send(int clientfd, int code){
	if (tab_request[clientfd].responding == 2)
	{
		_entity(code, clientfd);
		tab_request[clientfd].responding = 3;
	}
	if (tab_request[clientfd].responding == 3)
	{
		size_t	val = tab_request[clientfd].r_buffer.size();
		
		if (val > MAXLINE)
			val = MAXLINE;
		if (!val)
			return (-10);
		val = write(clientfd, tab_request[clientfd].r_buffer.begin().base(), val);
		std::cout << "bonjour, ca a voullu suppr " << tab_request[clientfd].r_buffer << std::endl;
		tab_request[clientfd].r_buffer.erase(tab_request[clientfd].r_buffer.begin(), tab_request[clientfd].r_buffer.begin() + val);
		return (val);
	}
	return (0);
}