#include <iostream>
#include <string>
#include <fstream>

int main (int ac, char *av[]){
	if (ac != 2)
	{
		std::cout << "Need 1 argument, the config file\n";
		return (1);
	}
	std::string		ptr;
	std::fstream	file;

	file.open(av[1], std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Echec lecture fichier config\n";
		return (1);
	}
	while (std::getline(file, ptr))
		std::cout << ptr << std::endl;
	file.close();
	return (0);
}