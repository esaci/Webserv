#include "../include/w_library.hpp"

size_t		RP15::extract_body_check( void ){
	size_t	line = 0;
	DATA	tmp_data;

	for(DATA::iterator it = parse_data.begin(); it != parse_data.end(); it++, line++)
	{
		tmp_data.clear();
		for(;it < parse_data.end() && (*it == '\n'); it++)
			;
		for(; it < parse_data.end() && *it != '\n'; it++)
			tmp_data.push_back(*it);
		if (tmp_data.size() == 1)
			return (line);
	}
	return (0);
}

int			_post_read_cl(std::vector<pollfd>::iterator it){
	(void)it;
	return 0;
		// recvline.clear();
	// if ((n = recv(it->fd, recvline.begin().base(), MAXLINE, 0)) > 0)
		// tab_request[it->fd].parse_data.insert(tab_request[it->fd].parse_data.end(), recvline.begin().base(), recvline.begin().base() + n);
}

int			_post_read_ch(std::vector<pollfd>::iterator it){
	(void)it;
	return 0;
}

int			server_data::_post_server_read(std::vector<pollfd>::iterator it){
	// int n;

	// if (tab_request[it->fd].content_length.size())
	// 	return (_post_read_cl(it));
	return (_post_read_ch(it));
}

