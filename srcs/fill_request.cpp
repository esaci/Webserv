#include "../include/w_library.hpp"

int		RP15::fill_request(int code){
	DATA::value_type tab[] = "GET / HTTP/1.1\r\n\r\n";

	return_error = code;
	parse_data.assign(tab, tab + std::strlen((char*)tab));
	// r_buffer.clear();
	// r_body_buffer.clear();
	method.clear();
	return (-10);
}
