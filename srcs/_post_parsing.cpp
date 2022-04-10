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

int			server_data::_post_read_cl(std::vector<pollfd>::iterator it){
	int	n;

	recvline.clear();
	if ((n = recv(it->fd, recvline.begin().base(), MAXLINE, 0)) > 0)
		tab_request[it->fd].r_body_buffer.insert(tab_request[it->fd].r_body_buffer.end(), recvline.begin().base(), recvline.begin().base() + n);
	if (compare_size_cl(tab_request[it->fd].r_body_buffer.size(), tab_request[it->fd].content_length))
	{
		tab_request[it->fd].responding = 1;
		tab_request[it->fd].display_cpcr();
		return (-10);
	}
	return (0);
}

int			RP15::_post_first_body(DATA::iterator it){
	for (; it < parse_data.end() && (*it == '\n' || *it == '\r'); it++)
		;
	r_body_buffer.assign(it, parse_data.end());
	parse_data.clear();
	if (transfer_encoding == _data_init("chunked")){
		return (print_return("Ca passe bien par la", 0));
	}
	if (compare_size_cl(r_body_buffer.size(), content_length))
	{
		responding = 1;
		display_cpcr();
		return (0);
	}
	return (1);
}

int			server_data::_post_read_ch(std::vector<pollfd>::iterator it){
	int n;
	if ((n = recv(it->fd, recvline.begin().base(), MAXLINE, 0)) > 0)
		tab_request[it->fd].r_body_buffer.insert(tab_request[it->fd].r_body_buffer.end(), recvline.begin().base(), recvline.begin().base() + n);
	if (0)
	{
		tab_request[it->fd].responding = 1;
		tab_request[it->fd].display_cpcr();
		return (-10);
	}
	std::cout << tab_request[it->fd].r_body_buffer;
	exit(1);
	return (0);
}

int			server_data::_post_server_read(std::vector<pollfd>::iterator it){
	if (tab_request[it->fd].content_length.size())
		return (_post_read_cl(it));
	return (_post_read_ch(it));
}

