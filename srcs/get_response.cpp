#include "../include/w_library.hpp"

int	server_data::_get_index(int clientfd){
	std::fstream	fs;
	parse_temp.clear();
	// size_t			tmp, len;
	
	std::cout << "Ca va sur index\n";
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	char_buff.clear();
	fs.open(TMPINDEX, std::fstream::in);
	if (!fs)
		return (_get_error_404(clientfd));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(char_buff.begin().base(), MAXLINE);
	while (fs.gcount()){
		parse_temp.insert(parse_temp.end(), char_buff.begin().base(), char_buff.begin().base() + fs.gcount());
		fs.read(char_buff.begin().base(), MAXLINE);
	}
	tab_request[clientfd].ressource = _data_init(TMPINDEX);
	_entity(200, _entity_ctype(clientfd));
	return (write(clientfd, parse_temp.begin().base(), parse_temp.size()));
}

int	server_data::_get_favicon(int clientfd){
	
	std::fstream	fs;
	parse_temp.clear();
	
	std::cout << "Ca va sur favicon\n";

	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	char_buff.clear();
	fs.open(TMPFAVICO, std::fstream::in);
	if (!fs)
		return (_get_error_404(clientfd));
	// std::cout << TMPFAVICO << " est l'endroit ou jvais chercher lindex\n";
	fs.read(char_buff.begin().base(), MAXLINE);
	while (fs.gcount()){
		parse_temp.insert(parse_temp.end(), char_buff.begin().base(), char_buff.begin().base() + fs.gcount());
		fs.read(char_buff.begin().base(), MAXLINE);
	}
	tab_request[clientfd].ressource = _data_init(TMPFAVICO);
	_entity(200, _entity_ctype(clientfd));
	std::cout << "Ca a bien ecrit donc wtf\n";
	return (write(clientfd, parse_temp.begin().base(), parse_temp.size()));
}

int	server_data::_get_error_400(int clientfd){
	std::fstream	fs;
	parse_temp.clear();
	
	std::cout << "Ca va sur 400\n";
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	char_buff.clear();
	fs.open(ERRORFILE_400, std::fstream::in);
	if (!fs)
		return (print_return("ERROR READ DU FICHIER _GET_ERROR", 1));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(char_buff.begin().base(), MAXLINE);
	while (fs.gcount()){
		parse_temp.insert(parse_temp.end(), char_buff.begin().base(), char_buff.begin().base() + fs.gcount());
		fs.read(char_buff.begin().base(), MAXLINE);
	}
	std::cout << "Jai bien acces a la donne " << tab_request[clientfd].ressource << " !\n";
	_entity_no_accept(400, "text/html");
	return (write(clientfd, parse_temp.begin().base(), parse_temp.size()));
}

int	server_data::_get_error_404(int clientfd){
	std::fstream	fs;
	parse_temp.clear();
	
	// Necessite de check si líndex est une simple page html?
	// prend un index par default pour linstant mal
	char_buff.clear();
	fs.open(ERRORFILE_404, std::fstream::in);
	if (!fs)
		return (print_return("ERROR READ DU FICHIER _GET_ERROR", 1));
	// std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	fs.read(char_buff.begin().base(), MAXLINE);
	while (fs.gcount()){
		parse_temp.insert(parse_temp.end(), char_buff.begin().base(), char_buff.begin().base() + fs.gcount());
		fs.read(char_buff.begin().base(), MAXLINE);
	}
	std::cout << "Jai bien acces a la donne " << tab_request[clientfd].ressource << " !\n";
	_entity_no_accept(404, "text/html");
	return (write(clientfd, parse_temp.begin().base(), parse_temp.size()));
}
