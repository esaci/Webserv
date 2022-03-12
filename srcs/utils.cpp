#include "../include/w_library.hpp"

DATA _data_init(std::string arg)
{
	DATA tmp;

	tmp.assign(arg.begin(), arg.end());
	return (tmp);
}