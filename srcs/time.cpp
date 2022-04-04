#include "../include/w_library.hpp"


int		RP15::_time_init( void ){
	char buf[200];
	
	time_client = std::time(0);
	std::tm* now = std::localtime(&time_client);
	strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", now);
	// std::cout << "La request a ete lance a " << buf << std::endl;
	return (0);
}

int		server_data::_time_maj( void )
{
	char buf[200];
	// size_t	i = 0;

	time_server = std::time(0);
	std::tm* now = std::localtime(&time_server);
	strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", now);
	// std::cout << "Le temps de server est " << buf << std::endl;	
	// if (tab_request.size())
		// std::cout << "On a donc une diff time de :\n";
	// for (R_DATA::iterator it = tab_request.begin(); it != tab_request.end(); it++, i++)
	// {
		// if (it->first == serverfd)
			// std::cout << "Server existe Depuis " << difftime(time_server, it->second.time_client) << std::endl;
		// else
			// std::cout << "Client " << i << " existe depuis " << difftime(time_server, it->second.time_client) << " sa ressource est " << it->second.ressource << std::endl;
	// }
	return (0);
}