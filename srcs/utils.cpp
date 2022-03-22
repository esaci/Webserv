#include "../include/w_library.hpp"

DATA _data_init(std::string arg)
{
	DATA tmp;

	tmp.assign(arg.begin(), arg.end());
	return (tmp);
}

char *_d_s(DATA &arg)
{
	arg.push_back('\0');
	return ((char*)arg.begin().base());
}

void	_data_begin(DATA &buff, std::string arg)
{
	buff.insert(buff.begin(), arg.begin(), arg.end());
}

int	print_return(std::string ptr, int value)
{
	std::cerr << ptr << std::endl;
	return (value);
}