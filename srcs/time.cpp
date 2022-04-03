#include "../include/w_library.hpp"

signed int	time_calcul(int time, signed int sectime)
{
	int	res;

	res = (time * 1000) + (sectime / 1000);
	return (res);
}

int		RP15::_time_init( void ){
	char buf[200];
	
	time_client = std::time(0);
	std::tm* now = std::localtime(&time_client);
	strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", now);
	std::cout << "La request a ete lance " << buf << std::endl;	
	return (0);
}

int		server_data::_time_maj( void )
{
	char buf[200];
	
	time_server = std::time(0);
	std::tm* now = std::localtime(&time_server);
	strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", now);
	
	std::cout << "Le temps de server est " << buf << std::endl;	
	return (0);
}

