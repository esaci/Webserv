#include "../include/w_library.hpp"
// curl -v -d 'salut le monde' -H "Transfer-Encoding: chunked" -X POST localhost:80/uploads
size_t		RP15::extract_body_check( void ){
	size_t	line = 0, i;

	for(DATA::iterator it = parse_data.begin(); it < parse_data.end(); it++, line++)
	{
		i = 0;
		for(;it < parse_data.end() && (*it == '\n'); it++)
			;
		for(; it < parse_data.end() && *it != '\n'; it++)
			i++;
		if (i == 1 && it != parse_data.end())
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
	// return (_post_read_ch(it));
	(void)it;
	return 0;
}

