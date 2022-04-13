#include "../include/w_library.hpp"

int		RP15::fill_request(int code, std::vector<struct pollfd>::iterator it){
	DATA::value_type tab[] = "GET / HTTP/1.0\r\n\r\n";

	if (!return_error)
		return_error = code;
	parse_data.assign(tab, tab + std::strlen((char*)tab));
	request_ready();
	it->events = POLLOUT | POLLERR | POLLHUP;
	responding = 1;
	return (-10);
}
