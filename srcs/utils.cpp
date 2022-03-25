#include "../include/w_library.hpp"

DATA _data_init(std::string arg)
{
	DATA tmp;

	tmp.assign(arg.begin(), arg.end());
	return (tmp);
}

char *_d_s(DATA &arg){return ((char*)arg.begin().base());}

void	_data_begin(DATA &buff, std::string arg)
{
	buff.insert(buff.begin(), arg.begin(), arg.end());
}

int	print_return(std::string ptr, int value)
{
	std::cerr << ptr << std::endl;
	return (value);
}

DATA	_link_root_init(std::string root, DATA &ressource){
	ressource.insert(ressource.begin(), root.begin(), root.end());
	return (ressource);
}

void	dec_to_hexa(DATA &buff, DATA::iterator it, size_t decimal_value)
{
	std::stringstream ss;

	ss << std::hex << decimal_value; // int decimal_value
	std::string res ( ss.str() );
	buff.insert(it, res.begin(), res.end());
}

size_t	hexa_to_dec(DATA &buff){
	size_t decimal_value;

	buff.push_back('\0');
	decimal_value = std::strtol((char*)buff.begin().base(), NULL, 16);
	buff.pop_back();
	return (decimal_value);
}

bool	compare_size_cl(size_t len, DATA &buff){
	size_t buff_len = std::strtol((char*)buff.begin().base(), NULL, 10);
	std::cout << "On a len puis buff_len" << len << " " << buff_len << std::endl;
	return (len == buff_len);
}