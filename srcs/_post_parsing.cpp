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
		last_step = 0, last_size = 0, last_remove = 0;
		return (1);
	}
	if (compare_size_cl(r_body_buffer.size(), content_length))
	{
		responding = 1;
		display_cpcr();
		return (0);
	}
	return (1);
}

int			RP15::_delete_number( void ){
	if ((r_body_buffer.size() - last_step) < last_size)
		return (0);
	DATA::iterator it, it2;

	it = r_body_buffer.begin() + last_step + last_size - last_remove;
	for (it2 = it; it2 < r_body_buffer.end() && *it2 != '\n' && *it2 != '\r'; it2++)
		;
	tmp_data.assign(it, it2);
	last_size = hexa_to_dec(tmp_data);
	last_remove = (it2 - it);
	for (; it2 < r_body_buffer.end() && (*it2 == '\n' || *it2 == '\r'); it2++)
		;
	last_step = it2 - r_body_buffer.begin();
	r_body_buffer.erase(it, it2);
	if (!last_size)
		return (1);
	return (_delete_number());
}

int			server_data::_post_read_ch(std::vector<pollfd>::iterator it){
	int n = 0;
	recvline.clear();
	if ((n = recv(it->fd, recvline.begin().base(), MAXLINE, 0)) > 0)
		tab_request[it->fd].r_body_buffer.insert(tab_request[it->fd].r_body_buffer.end(), recvline.begin().base(), recvline.begin().base() + n);
	if (tab_request[it->fd]._delete_number())
		{
			if (*(--tab_request[it->fd].r_body_buffer.end()) == '\n')
				tab_request[it->fd].r_body_buffer.pop_back();
			tab_request[it->fd].responding = 1;
			tab_request[it->fd].display_cpcr();
			return (-10);
		}
	// std::cout << tab_request[it->fd].r_body_buffer;
	return (0);
}

int			server_data::_post_server_read(std::vector<pollfd>::iterator it){
	if (tab_request[it->fd].content_length.size())
		return (_post_read_cl(it));
	return (_post_read_ch(it));
}

