#include "../include/w_library.hpp"

void	RP15::_set_info(size_t len, std::string &tmp_i, struct dirent *tmp_f)
{
	struct stat st;

	tmp_i.assign(ressource.begin(), ressource.end());
	tmp_i.insert(tmp_i.end(), tmp_f->d_name, tmp_f->d_name + std::strlen(tmp_f->d_name));
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

int	RP15::_set_folder(DIR	*folder)
{
	if (*(ressource.end() - 2) != '/')
	{
		return_error = 301;
		redirection.reserve(ressource.size() + 2);
		redirection = retire_root(ressource);
		redirection.push_back('/');
		return (0);
	}
	std::set<std::string, indexcomp> ordering;
	std::map<std::string, std::string> date_taille;
	std::string tmp_s, tmp_i;

	ressource.push_back('\0');
	r_buffer = _data_init("<html>\n<head><title>Index of ");
	_data_end(r_buffer, (char*)retire_root(ressource).begin().base());
	_data_end(r_buffer, "</title></head>\n<body>\n<h1>Index of ");
	_data_end(r_buffer, (char*)retire_root(ressource).begin().base());
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
		_set_info(tmp_s.size(), tmp_i, tmp_f);
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

	tab_request[clientfd].ressource.push_back('\0');
	std::cout << "Comment ca j'ouvre ce fichier " << tab_request[clientfd].ressource << std::endl;
	if ((folder = opendir((char*)tab_request[clientfd].ressource.begin().base())))
		return (tab_request[clientfd]._set_folder(folder));
	else
		filefd = open((char*)tab_request[clientfd].ressource.begin().base(), O_RDONLY);
	tab_request[clientfd].ressource.pop_back();
	if (filefd < 0)
		return (1);
	tab_request[filefd]._time_init();
	files_to_clients[filefd] = clientfd;
	client_poll.fd = filefd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	tab_poll.push_back(client_poll);
	tab_request[clientfd].responding = 2;
	return (0);
}

