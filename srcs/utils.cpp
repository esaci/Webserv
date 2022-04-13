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
	if (std::strtol((char*)buff.begin().base(), NULL, 16) < 0)
		decimal_value = 0;
	buff.pop_back();
	return (decimal_value);
}

bool	compare_size_cl(size_t len, DATA &buff){
	buff.push_back('\0');
	size_t buff_len = std::strtol((char*)buff.begin().base(), NULL, 10);
	buff.pop_back();
	return (len == buff_len);
}

void	return_data_size(size_t len, DATA &buff){
	std::stringstream ss;

	ss << len; // int decimal_value
	std::string res ( ss.str() );
	buff.assign(res.begin(), res.end());
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

void	retire_tiret(DATA &buff){
	for (DATA::iterator it = buff.begin(); it < buff.end();)
	{
		if (*it == '-' || *it == '\0' || *it == '\n')
			buff.erase(it);
		else
			++it;
	}
	buff.pop_back();
	buff.push_back('\0');
}

std::vector<struct pollfd>::iterator _return_it_poll(int clientfd, std::vector<struct pollfd> &tab_poll)
{
	std::vector<struct pollfd>::iterator it;

	for (it = tab_poll.begin(); it < tab_poll.end() && it->fd != clientfd; it++)
		;
	return (it);
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

void			retire_doublon_slash(DATA &ressource){
	for(size_t i = 0; i < (ressource.size() - 1);)
	{
		if (*(ressource.begin() + i) == '/' && *(ressource.begin() + i + 1) == '/')
			ressource.erase(ressource.begin() + i + 1);
		else
			i++;
	}
}

