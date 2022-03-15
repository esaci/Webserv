#include "../include/w_library.hpp"

int	server_data::_get_index(int clientfd){
	char			recvline[MAXLINE + 1];
	std::fstream	fs;
	DATA			buff;
	// size_t			tmp, len;
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	fs.open(TMPINDEX, std::fstream::in);
	if (!fs)
		return (_get_error_404(clientfd));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	_entity(buff, 200, "text/html");
	return (write(clientfd, buff.begin().base(), buff.size()));
}

int	server_data::_get_favicon(int clientfd){
	char			recvline[MAXLINE + 1];
	std::fstream	fs;
	DATA			buff;
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	fs.open(TMPFAVICO, std::fstream::in);
	if (!fs)
		return (_get_error_404(clientfd));
	// std::cout << TMPFAVICO << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	_entity(buff, 200, "image/x-icon");
	return (write(clientfd, buff.begin().base(), buff.size()));
}

int	server_data::_get_error_400(int clientfd){
	char			recvline[MAXLINE + 1];
	std::fstream	fs;
	DATA			buff;
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	fs.open(ERRORFILE_400, std::fstream::in);
	if (!fs)
		return (print_return("ERROR READ DU FICHIER _GET_ERROR", 1));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	_entity_no_accept(buff, 400, "text/html");
	return (write(clientfd, buff.begin().base(), buff.size()));
}

int	server_data::_get_error_404(int clientfd){
	char			recvline[MAXLINE + 1];
	std::fstream	fs;
	DATA			buff;
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	fs.open(ERRORFILE_404, std::fstream::in);
	if (!fs)
		return (print_return("ERROR READ DU FICHIER _GET_ERROR", 1));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(recvline, MAXLINE);
	while (fs.gcount()){
		buff.insert(buff.end(), recvline, recvline + fs.gcount());
		fs.read(recvline, MAXLINE);
	}
	_entity_no_accept(buff, 404, "text/html");
	return (write(clientfd, buff.begin().base(), buff.size()));
}
