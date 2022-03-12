#include "../include/w_library.hpp"

int	_get_index(DATA &buff, int clientfd){
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	std::fstream fs;
	fs.open(TMPINDEX, std::fstream::in);
	if (!fs)
		print_return("ERROR READ DU FICHIER", 1);
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	// _entity(codes, buff, 300);
	n = write(clientfd, buff.begin().base(), buff.size());
	return (n);
}