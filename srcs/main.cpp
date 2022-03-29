#include "../include/w_library.hpp"
// handle_line_request il faut que mettre en palce le system pour renvoye la page d'erreurcorrespondant a l'erreur si jamais la request line est pas au bon for,mat

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
	server_data	*serv = new server_data(file);

	serv->_server();
	delete serv;
	return (0);
}