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

void	_data_end(DATA &buff, std::string arg)
{
	buff.insert(buff.end(), arg.begin(), arg.end());
}


int	print_return(std::string ptr, int value)
{
	std::cerr << ptr << std::endl;
	return (value);
}

DATA	_link_root_init(std::string root, DATA &ressource){
	if (*ressource.begin() != '/')
		ressource.insert(ressource.begin(), '/');
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

DATA	retire_root(DATA &buff, std::string &root){
	if (buff.size() < root.size())
		return (buff);
	DATA tmp(buff.begin() + root.size(), buff.end());
	tmp.pop_back();
	return (tmp);
}


size_t	hexa_to_dec(DATA &buff){
	size_t decimal_value;

	buff.push_back('\0');
	decimal_value = std::strtol((char*)buff.begin().base(), NULL, 16);
	buff.pop_back();
	return (decimal_value);
}

bool	compare_size_cl(size_t len, DATA &buff){
	buff.push_back('\0');
	size_t buff_len = std::strtol((char*)buff.begin().base(), NULL, 10);
	buff.pop_back();
	return (len == buff_len);
}

bool indexcomp::operator()(const std::string& lhs, const std::string& rhs) const{
	bool l = false, r = false;

	if (*(--lhs.end()) == '/')
		l = true;
	if (*(--rhs.end()) == '/')
		r = true;
	if (l ^ r)
		return (l);
	std::less<std::string> comp;
	return (comp(lhs, rhs));
}

void	_erase_location(DATA &ressource, _MAP_ROOT &map_root, std::string &root)
{
	_MAP_ROOT::iterator it;

	for (it = map_root.begin(); it != map_root.end() && it->second != root; it++)
		;
	if (it != map_root.end() && it->first.size() > 1)
		ressource.erase(ressource.begin(), ressource.begin() + it->first.size() - 1);
	_link_root_init(root, ressource);
}
