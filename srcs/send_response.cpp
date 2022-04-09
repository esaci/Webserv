#include "../include/w_library.hpp"

int	server_data::_send(int clientfd, int code){
	if (tab_request[clientfd].responding == 3)
	{
		_entity(code, clientfd);
		tab_request[clientfd].responding = 4;
	}
	if (tab_request[clientfd].responding == 4)
	{
		size_t	val = tab_request[clientfd].r_buffer.size();
		int		value;
		if (val > MAXLINE)
			val = MAXLINE;
		if (!val)
			return (-10);
		value = write(clientfd, tab_request[clientfd].r_buffer.begin().base(), val);
		if (value > 0)
			tab_request[clientfd].r_buffer.erase(tab_request[clientfd].r_buffer.begin(), tab_request[clientfd].r_buffer.begin() + value);
		else
			return (-10);
		return (0);
	}
	return (0);
}