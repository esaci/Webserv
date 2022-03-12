#include "../include/w_library.hpp"

int	_get_index(int clientfd, C_DATA *codes){
	char			recvline[MAXLINE + 1];
	std::fstream	fs;
	DATA			buff;
	// size_t			tmp, len;
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	fs.open(TMPINDEX, std::fstream::in);
	if (!fs)
		return (print_return("ERROR READ DU FICHIER", 1));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	_entity(codes, buff, 200, "text/html");
	return (write(clientfd, buff.begin().base(), buff.size()));
}

int	_get_favicon(int clientfd, C_DATA *codes){
	char			recvline[MAXLINE + 1];
	std::fstream	fs;
	DATA			buff;
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	fs.open(TMPFAVICO, std::fstream::in);
	if (!fs)
		return (print_return("ERROR READ DU FICHIER", 1));
	// std::cout << TMPFAVICO << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	_entity(codes, buff, 200, "image/x-icon");
	return (write(clientfd, buff.begin().base(), buff.size()));
}

int	_get_error(int clientfd, C_DATA *codes){
	char			recvline[MAXLINE + 1];
	std::fstream	fs;
	DATA			buff;
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	fs.open(ERRORFILE, std::fstream::in);
	if (!fs)
		return (print_return("ERROR READ DU FICHIER", 1));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	_entity(codes, buff, 400, "texte/html");
	return (write(clientfd, buff.begin().base(), buff.size()));
}
