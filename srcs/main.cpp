#include "../include/w_library.hpp"

int main (int ac, char *av[]){
	std::fstream	file;
	
	if (!ac || ac > 2)
	{
		std::cout << "Need 1 argument, the config file\n";
		return (1);
	}
	if (ac == 1)
		file.open("config_file/default.conf", std::fstream::in);
	else
		file.open(av[1], std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Echec lecture fichier config\n";
		return (1);
	}
	server_data	serv(file);

	serv._server();
	return (0);
}