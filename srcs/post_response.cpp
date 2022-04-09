#include "../include/w_library.hpp"
// 
int		RP15::_post_cgi(server_data *d_s, int clientfd){
	if (responding < 2)
	{
		DATA	temp;
		int fd;
		if (method == _data_init("GET"))
		{
			DATA::iterator it;
			for (it = ressource.begin(); it < ressource.end() && *it != '?'; it++)
				;
			// faire ++it si it != ressource.end(), pour ne pas avoir ?, OSCAR
			r_body_get.assign(it, ressource.end());
			ressource.erase(it, ressource.end());
		}
		temp = _data_init(FILE_CGI);
		temp.push_back('\0');
		fd = open((char*)temp.begin().base(), O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (print_return("FILE_CGI pas dispo !", -10));
		basic_cgi(d_s, fd);
		if (d_s->_set_file(clientfd))
			return (d_s->_get_error_404(clientfd));
		return (0);
	}
	return (d_s->_send(clientfd, 200));
}

bool check_bad_inf(DATA &ct, DATA &buff)
{
	std::string	v1("multipart/form-data;");
	std::string	v2;
	(void)buff;
	//std::string v3;
	if (ct.size() < 20) {return (1);}
	for(DATA::iterator it = ct.begin(); (it != ct.end() && it != (ct.begin() + 20)); it++)
		v2.push_back(*it);
	if (v1 != v2) {return (1);}
	/*for (DATA:iterator it = buff.begin(); (it != buff.end() && *it != '\n'); it++)
		v3.push_back(*it);*/
	
	return (0);
}

void	parse_body_buff(DATA &buff)
{
	std::cout << buff << std::endl;
}

int	server_data::_post_upload(int clientfd)
{
	(void)clientfd;
	std::string root = tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].get_root((char*)tab_request[clientfd].ressource.begin().base());
	std::cout << root << std::endl;
	std::cout << "-----------------raph----------------------" << std::endl;
	check_bad_inf(tab_request[clientfd].content_type, tab_request[clientfd].r_body_buffer);
	std::cout << "raph:" << tab_request[clientfd].content_type << std::endl;
	parse_body_buff(tab_request[clientfd].r_body_buffer);
	std::cout << "-----------------raph----------------------" << std::endl;
	// TOUTE LES INFOS DU CLIENT SONT SUR tab_request[clientfd]
	// Pour avoir ladresse et le port du client, sockets_to_hosts[clientfd]
	// if (responding < 2)
	// {
	//
	// }
	exit(1);
	return (_send(clientfd, 200));
}