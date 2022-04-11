#include "../include/w_library.hpp"
// 
int		RP15::_post_cgi(server_data *d_s, int clientfd){
	if (responding < 2)
	{
		DATA	temp;
		int fd;
		ressource = u_ressource;
		if (method == _data_init("GET"))
		{
			DATA::iterator it;

			for (it = ressource.begin(); it < ressource.end() && *it != '?'; it++)
				;
			r_body_get.assign(it, ressource.end());
			ressource.erase(it, ressource.end());
		}
		temp = _data_init(FILE_CGI);
		temp.push_back('\0');
		fd = open((char*)temp.begin().base(), O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (print_return("FILE_CGI pas dispo !", -10));
		fcntl(fd, F_SETFL, O_NONBLOCK);
		basic_cgi(d_s, fd);
		if (d_s->_set_file(clientfd))
			return (d_s->_get_error_404(clientfd));
		return (0);
	}
	return (d_s->_send(clientfd, 200));
}

bool check_bad_inf(DATA &ct, DATA &body, std::string &file)
{
	std::string	v1("multipart/form-data;");
	std::string	v2;
	DATA::iterator it, it2, it3;
	size_t pos;
	DATA	webkit, checkwebkit;

	//std::string v3;
	for(it = ct.begin(); (it != ct.end() && it != (ct.begin() + v1.size())); it++)
			;
	v2.assign(ct.begin(), it);
	if (v1 != v2) {return (1);}
	for (it = body.begin(); it < body.end() && *it != '\n'; it++)
		;
	if (it == body.end())
		return (1);
	webkit.assign(body.begin(), it);
	it++;
	for (it2 = it; it2 < body.end() && *it2 != '\n'; it2++)
		;
	if (it2 == body.end())
		return (1);
	v2.assign(it, it2);
	pos = v2.find("filename=\"");
	if (pos == std::string::npos)
		return (1);
	v1.assign(v2.begin() + pos + std::strlen("filename=\""), v2.end());
	pos = v1.find("\"");
	if (pos == std::string::npos)
		return (1);
	v1 = v1.substr(0, pos);
	++it2;
	for(pos = 0; it2 < body.end() && pos < 2; it2++)
	{
		if (*it2 == '\n')
			pos++;
	}
	if (pos < 2)
		return (1);
	body.erase(body.begin(), it2);
	for(it2 = (body.end() - 2); it2 > body.begin() && *it2 != '\n'; it2--)
		;
	if (it2 == body.begin())
		return (1);
	checkwebkit.assign(it2--, body.end());
	retire_tiret(webkit);
	retire_tiret(checkwebkit);
	if (checkwebkit != webkit)
		return (1);
	body.erase(it2, body.end());
	file = v1;
	return (0);
}

bool	server_data::open_file_upload(int clientfd, std::string &file)
{
	int fd;

	file = tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].path_upload_dir + file;
	if ((fd = open(file.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0)
		return 1;
	tab_request[clientfd].responding = 2;
	client_poll.fd = fd;
	client_poll.events = POLLOUT;
	client_poll.revents = 0;
	tab_poll.push_back(client_poll);
	files_to_clients[fd] = clientfd;
	// write(fd, tab_request[clientfd].r_body_buffer.begin().base(), tab_request[clientfd].r_body_buffer.size());
	return (0);
}

int	server_data::_post_upload(int clientfd)
{
	if (tab_request[clientfd].responding < 2)
	{
		std::string file;
		std::string root = tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]][0].get_root((char*)tab_request[clientfd].u_ressource.begin().base());

		if (check_bad_inf(tab_request[clientfd].content_type, tab_request[clientfd].r_body_buffer, file))
			tab_request[clientfd].fill_request(400, _return_it_poll(clientfd, tab_poll));
		else if (open_file_upload(clientfd, file))
			tab_request[clientfd].fill_request(400, _return_it_poll(clientfd, tab_poll));
		return (0);
	}
	if (tab_request[clientfd].responding == 3)
		tab_request[clientfd].fill_request(200, _return_it_poll(clientfd, tab_poll));
	return (0);
}