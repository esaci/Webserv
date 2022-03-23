#include "../include/w_library.hpp"

int	server_data::_get_index(int clientfd){
	std::cout << TMPINDEX << " est l'endroit ou jvais chercher lindex\n";
	char_buff.clear();
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(TMPINDEX);
		tab_request[clientfd].ressource.push_back('\0');
		tab_request[clientfd].fs.open(_d_s(tab_request[clientfd].ressource), std::fstream::in);
		tab_request[clientfd].ressource.pop_back();
		tab_request[clientfd].responding = 2;
	}
	std::cerr << "Ca rentre ici avec une valeur de " << tab_request[clientfd].responding << std::endl;
	if (!tab_request[clientfd].fs)
		return (_get_error_404(clientfd));
	tab_request[clientfd].fs.read(char_buff.begin().base(), MAXLINE);
	tab_request[clientfd].r_buffer.insert(tab_request[clientfd].r_buffer.end(), char_buff.begin().base(), char_buff.begin().base() + tab_request[clientfd].fs.gcount());
	return (_send(clientfd, 200));
}

int	server_data::_get_favicon(int clientfd){
	std::cout << TMPFAVICO << " est l'endroit ou jvais chercher lindex\n";
	char_buff.clear();
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(TMPFAVICO);
		tab_request[clientfd].ressource.push_back('\0');
		tab_request[clientfd].fs.open(_d_s(tab_request[clientfd].ressource), std::fstream::in);
		tab_request[clientfd].ressource.pop_back();
		tab_request[clientfd].responding = 2;
	}
	std::cerr << "Ca rentre ici avec une valeur de " << tab_request[clientfd].responding << std::endl;
	if (!tab_request[clientfd].fs)
		return (_get_error_404(clientfd));
	tab_request[clientfd].fs.read(char_buff.begin().base(), MAXLINE);
	if (tab_request[clientfd].fs.gcount())
		tab_request[clientfd].r_buffer.insert(tab_request[clientfd].r_buffer.end(), char_buff.begin().base(), char_buff.begin().base() + tab_request[clientfd].fs.gcount());
	return (_send(clientfd, 200));
}

int	server_data::_get_error_400(int clientfd){
	std::cout << ERRORFILE_400 << " est l'endroit ou jvais chercher lindex\n";
	char_buff.clear();
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(ERRORFILE_400);
		tab_request[clientfd].ressource.push_back('\0');
		tab_request[clientfd].fs.open(_d_s(tab_request[clientfd].ressource), std::fstream::in);
		tab_request[clientfd].ressource.pop_back();
		tab_request[clientfd].responding = 2;
	}
	std::cerr << "Ca rentre ici avec une valeur de " << tab_request[clientfd].responding << std::endl;
	if (!tab_request[clientfd].fs)
		return (print_return("ERROR READ DU FICHIER _GET_ERROR 400", -10));
	tab_request[clientfd].fs.read(char_buff.begin().base(), MAXLINE);
	tab_request[clientfd].r_buffer.insert(tab_request[clientfd].r_buffer.end(), char_buff.begin().base(), char_buff.begin().base() + tab_request[clientfd].fs.gcount());
	return (_send(clientfd, 400));
}

int	server_data::_get_error_404(int clientfd){
	std::cout << ERRORFILE_404 << " est l'endroit ou jvais chercher lindex\n";
	char_buff.clear();
	if (tab_request[clientfd].responding < 2)
	{
		tab_request[clientfd].ressource = _data_init(ERRORFILE_404);
		tab_request[clientfd].ressource.push_back('\0');
		tab_request[clientfd].fs.open(_d_s(tab_request[clientfd].ressource), std::fstream::in);
		tab_request[clientfd].ressource.pop_back();
		tab_request[clientfd].responding = 2;
		printf("CA PASSE ICI AVEC %s\n", _d_s(tab_request[clientfd].ressource));
	}
	std::cerr << "Ca rentre ici avec une valeur de " << tab_request[clientfd].responding << std::endl;
	if (!tab_request[clientfd].fs)
		return (print_return("ERROR READ DU FICHIER _GET_ERROR 404", -10));
	tab_request[clientfd].fs.read(char_buff.begin().base(), MAXLINE);
	tab_request[clientfd].r_buffer.insert(tab_request[clientfd].r_buffer.end(), char_buff.begin().base(), char_buff.begin().base() + tab_request[clientfd].fs.gcount());
	return (_send(clientfd, 404));
}
