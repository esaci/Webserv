#include "../include/w_library.hpp"

// Je peux en accept plusieurs potentiellement, mais ca me sonne complique
int	server_data::_new_client(std::vector<struct pollfd>::iterator it){
	int	clientfd = accept(serverfd, (SA*) NULL, NULL);

	// std::cout << "Connection Cree pour le fd " << clientfd << " !\n";
	if (clientfd < 0)
		return (print_return("Error: accept", 1));	
	client_poll.fd = clientfd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	tab_poll.insert(tab_poll.end() , client_poll);
	return (0);
	(void)it;
}
int	server_data::handle_line_request(std::vector<struct pollfd>::iterator it, size_t n){
	size_t	i = 0, step3 = 0;
	int	step = 0;

	if (!tab_request[it->fd].parse_data.size())
	{
		for(; i < n && (recvline[i] == '\n' || recvline[i] == '\r'); i++)
			;
		if (i == n)
			return (1);
	}
	tab_request[it->fd].parse_data.insert(tab_request[it->fd].parse_data.end(), recvline.begin().base() + i, recvline.begin().base() + n);
	if (tab_request[it->fd].r_l_v)
		return (0);
	for (i = 0; i < tab_request[it->fd].parse_data.size() && tab_request[it->fd].parse_data[i] != '\n'; i++)
	{
		if (!step && (tab_request[it->fd].parse_data[i] < 'A' || tab_request[it->fd].parse_data[i] > 'Z') && (!i || tab_request[it->fd].parse_data[i] != ' '))
			return (tab_request[it->fd].fill_request(401));
		if (step == 1)
		{
			if (tab_request[it->fd].parse_data[i] != '/')
				return (tab_request[it->fd].fill_request(402));
			step++;
		}
		if (step == 3 && !step3)
			step3 = i;
		if (tab_request[it->fd].parse_data[i] == ' ')
		{
			for (;i < tab_request[it->fd].parse_data.size() && tab_request[it->fd].parse_data[i] == ' '; i++)
				;
			i--;
			if (i < tab_request[it->fd].parse_data.size())
				step++;
		}
	}
	if (i == tab_request[it->fd].parse_data.size() || tab_request[it->fd].parse_data[i] != '\n')
		return (0);
	if (step != 3)
		return (tab_request[it->fd].fill_request(403));
	tab_request[it->fd].tmp_data.assign(tab_request[it->fd].parse_data.begin() + step3, tab_request[it->fd].parse_data.begin() + i - 1);
	// tab_request[it->fd].tmp_data.push_back('\0');
	if (tab_request[it->fd].tmp_data != _data_init("HTTP/1.1") && tab_request[it->fd].tmp_data != _data_init("HTTP/1.0"))
		return (tab_request[it->fd].fill_request(404));
	tab_request[it->fd].r_l_v = true;
	tab_request[it->fd].tmp_data.clear();
	return (0);
}

int	server_data::_read_client(std::vector<struct pollfd>::iterator it)
{
	int		n;

	recvline.clear();
	if ((n = recv(it->fd, recvline.begin().base(), MAXLINE, 0)) > 0)
		handle_line_request(it, n);
	if (n < 0)
		return (print_return("Error: recv", 1));
	if (tab_request[it->fd].is_ready())
	{
		if (!tab_request[it->fd].request_ready())
			return (-10);
	}
	return(0);
}

int	server_data::_server_read(std::vector<struct pollfd>::iterator it)
{
	if (it->fd == serverfd)
		return (_new_client(it));
	return (_read_client(it));
}

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
	tab_request[clientfd].r_buffer = _data_init("<html>\n<head><title>WEBSERV Index of /</title></head>\n<body>\n<h1>Index of /</h1><hr><pre>\n");
	for	(struct dirent	*tmp_f = readdir(folder); tmp_f; tmp_f = readdir(folder))
	{
		_data_end(tab_request[clientfd].r_buffer, "<a href=\"");
		_data_end(tab_request[clientfd].r_buffer, tmp_f->d_name);
		if (tmp_f->d_type == DT_DIR)
			_data_end(tab_request[clientfd].r_buffer, "/");
		_data_end(tab_request[clientfd].r_buffer, "\">");
		_data_end(tab_request[clientfd].r_buffer, tmp_f->d_name);
		if (tmp_f->d_type == DT_DIR)
			_data_end(tab_request[clientfd].r_buffer, "/");
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
