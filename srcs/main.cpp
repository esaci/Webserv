#include "../include/w_library.hpp"

int main (int ac, char *av[]){
	p_conf *conf;

	if (!ac || ac > 2)
	{
		std::cout << "Need 1 argument, the config file\n";
		return (1);
	}
	std::string		ptr;
	std::fstream	file;

	if (ac == 1)
		file.open("config_file/default.conf", std::fstream::in);
	else
		file.open(av[1], std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Echec lecture fichier config\n";
		return (1);
	}
	conf = new p_conf(file);
	// Necessite de parsing du fichier conf
	// Gestion error si necessaire
	//Creation du server
	_server();
	// while (std::getline(file, ptr))
		// std::cout << ptr << std::endl;
	delete conf;
	return (0);
}