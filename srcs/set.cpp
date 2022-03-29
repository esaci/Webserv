#include "../include/w_library.hpp"

int	server_data::_set_folder(DIR	*folder, int clientfd)
{
	if (*(tab_request[clientfd].ressource.end() - 2) != '/')
	{
		tab_request[clientfd].return_error = 301;
		tab_request[clientfd].redirection.reserve(tab_request[clientfd].ressource.size() + 2);
		tab_request[clientfd].redirection = retire_root(tab_request[clientfd].ressource); 
		tab_request[clientfd].redirection.push_back('/');
		return (0);
	}
	std::set<std::string, indexcomp> ordering;
	std::string tmp_s;

	tab_request[clientfd].ressource.push_back('\0');
	tab_request[clientfd].r_buffer = _data_init("<html>\n<head><title>Index of ");
	_data_end(tab_request[clientfd].r_buffer, (char*)retire_root(tab_request[clientfd].ressource).begin().base());
	_data_end(tab_request[clientfd].r_buffer, "</title></head>\n<body>\n<h1>Index of ");
	_data_end(tab_request[clientfd].r_buffer, (char*)retire_root(tab_request[clientfd].ressource).begin().base());
	_data_end(tab_request[clientfd].r_buffer, "</h1><hr><pre>\n");
	tab_request[clientfd].ressource.pop_back();
	for	(struct dirent	*tmp_f = readdir(folder); tmp_f; tmp_f = readdir(folder))
	{
		if (std::string(tmp_f->d_name) == ".")
			continue ;
		tmp_s.assign(tmp_f->d_name);
		if (tmp_f->d_type == DT_DIR)
			tmp_s.push_back('/');
		ordering.insert(tmp_s);
	}
	for(std::set<std::string>::iterator it = ordering.begin(); it != ordering.end(); it++)
	{
		_data_end(tab_request[clientfd].r_buffer, "<a href=\"");
		_data_end(tab_request[clientfd].r_buffer, *it);
		_data_end(tab_request[clientfd].r_buffer, "\">");
		_data_end(tab_request[clientfd].r_buffer, *it);
		_data_end(tab_request[clientfd].r_buffer, "</a>\n");
	}
	_data_end(tab_request[clientfd].r_buffer, "</pre><hr></body>\n</html>");
	_data_end(tab_request[clientfd].r_buffer, "\0");
	std::cout << tab_request[clientfd].r_buffer << std::endl;
	tab_request[clientfd].ressource.pop_back();
	tab_request[clientfd].responding = 3;
	closedir(folder);
	return (0);
}

int	server_data::_set_file(int clientfd){
	int filefd;
	DIR *folder;
	
	tab_request[clientfd].ressource.push_back('\0');
	if ((folder = opendir((char*)tab_request[clientfd].ressource.begin().base())))
		return (_set_folder(folder, clientfd));
	else
		filefd = open((char*)tab_request[clientfd].ressource.begin().base(), O_RDONLY);
	tab_request[clientfd].ressource.pop_back();
	if (filefd < 0)
		return (1);
	files_to_clients[filefd] = clientfd;
	client_poll.fd = filefd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	tab_poll.push_back(client_poll);
	tab_request[clientfd].responding = 2;
	return (0);
}

