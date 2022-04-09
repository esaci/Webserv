#include "../include/w_library.hpp"

void	RP15::_set_info(size_t len, std::string &tmp_i, struct dirent *tmp_f, std::string &root)
{
	struct stat st;

	tmp_i = root;
	tmp_i.insert(tmp_i.end(), u_ressource.begin(), u_ressource.end());
	tmp_i.insert(--tmp_i.end(), tmp_f->d_name, tmp_f->d_name + std::strlen(tmp_f->d_name));
	tmp_i.push_back('\0');
	if (stat(tmp_i.c_str(), &st) == 0)
	{
		std::stringstream ss;
		struct tm *tm;
		char buf[200];
		std::string tmp_b;

		tmp_i.clear();
		tm = localtime(&(st.st_mtime));
		strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", tm);
		if (67 > len)
			tmp_i.resize(67 - len, ' ');
		tmp_i.insert(tmp_i.end(), buf, buf + std::strlen(buf));
		if (tmp_f->d_type == DT_DIR)
			tmp_b.assign("-");
		else
		{
			ss << (long long)st.st_size;
			tmp_b.assign(ss.str());
		}
		if (34 + tmp_i.size() > tmp_b.size())
			tmp_i.resize(34 + tmp_i.size() - tmp_b.size(), ' ');
		tmp_i.insert(tmp_i.end(), tmp_b.begin(), tmp_b.end());
	}
	else
		tmp_i.clear();
	tmp_i.push_back('\n');
}

int	RP15::_set_folder(DIR	*folder, std::string &root, bool autoindex)
{
	if (!autoindex)
	{
		return_error = 400;
		return (0);
	}
	if (*(u_ressource.end() - 2) != '/')
	{
		return_error = 301;
		redirection.reserve(ressource.size() + 2);
		redirection = retire_root(u_ressource, root);
		redirection.pop_back();
		redirection.push_back('/');
		return (0);
	}
	std::set<std::string, indexcomp> ordering;
	std::map<std::string, std::string> date_taille;
	std::string tmp_s, tmp_i;

	ressource.push_back('\0');
	r_buffer = _data_init("<html>\n<head><title>Index of ");
	_data_end(r_buffer, (char*)retire_root(ressource, root).begin().base());
	_data_end(r_buffer, "</title></head>\n<body>\n<h1>Webserv/1.0 Index of ");
	_data_end(r_buffer, (char*)retire_root(ressource, root).begin().base());
	_data_end(r_buffer, "</h1><hr><pre>\n");
	ressource.pop_back();
	for	(struct dirent	*tmp_f = readdir(folder); tmp_f; tmp_f = readdir(folder))
	{
		if (std::string(tmp_f->d_name) == ".")
			continue ;
		tmp_s.assign(tmp_f->d_name);
		if (tmp_f->d_type == DT_DIR)
			tmp_s.push_back('/');
		ordering.insert(tmp_s);
		_set_info(tmp_s.size(), tmp_i, tmp_f, root);
		date_taille.insert(std::pair<std::string, std::string>(tmp_s, tmp_i));
	}
	for(std::set<std::string>::iterator it = ordering.begin(); it != ordering.end(); it++)
	{
		_data_end(r_buffer, "<a href=\"");
		_data_end(r_buffer, *it);
		_data_end(r_buffer, "\">");
		_data_end(r_buffer, *it);
		_data_end(r_buffer, "</a>");
		_data_end(r_buffer, date_taille[*it]);
	}
	_data_end(r_buffer, "</pre><hr></body>\n</html>");
	_data_end(r_buffer, "\0");
	ressource.pop_back();
	responding = 3;
	closedir(folder);
	return (0);
}

int	server_data::_set_file(int clientfd){
	int filefd;
	DIR *folder;
	std::string root;
	static int i = 0;

	tab_request[clientfd].ressource.push_back('\0');
	root = tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].get_root((char*)tab_request[clientfd].u_ressource.begin().base());
	std::cout << root << " le root \n" << i++ << "\n" <<  tab_request[clientfd].ressource << " la ressource " << std::endl;
	if ((folder = opendir((char*)tab_request[clientfd].ressource.begin().base())))
		return (tab_request[clientfd]._set_folder(folder, root, tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].get_autoindex((char*)tab_request[clientfd].u_ressource.begin().base())));
	else
		filefd = open((char*)tab_request[clientfd].ressource.begin().base(), O_RDONLY);
	tab_request[clientfd].ressource.pop_back();
	if (filefd < 0)
	{
		tab_request[clientfd].return_error = 404;
		return (1);
	}
	if (!tab_request[clientfd].return_error)
		tab_request[filefd].time_client = tab_request[clientfd].time_client;
	tab_request[clientfd].r_buffer.clear();
	files_to_clients[filefd] = clientfd;
	client_poll.fd = filefd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	tab_poll.push_back(client_poll);
	tab_request[clientfd].responding = 2;
	return (0);
}
