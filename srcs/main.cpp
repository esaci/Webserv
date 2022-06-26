#include "../include/w_library.hpp"

int main (int ac, char *av[]){
	std::fstream	file;
	
	signal(SIGPIPE, SIG_IGN);
	if (!ac || ac > 2)
		return (print_return("Need 1 argument, the config file", 1));
	if (ac == 1)
		file.open("config_file/main2.conf", std::fstream::in);
	else
		file.open(av[1], std::fstream::in);
	if (!file.is_open())
		return (print_return("Echec lecture fichier config", 1));
	
	server_data	*serv = new server_data(file);
	if (serv->error_conf == 0)
		serv->_server();
	delete serv;
	return (0);
}