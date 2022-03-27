#include "../include/w_library.hpp"

int		RP15::fill_request(int code){
	std::string tmp_b("GET / HTTP/1.0\r\n\r\n");
	
	return_error = code;
	parse_data = _data_init(tmp_b);
	return (-10);
}
