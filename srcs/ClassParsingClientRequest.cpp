#include "../include/w_library.hpp"
#include "../include/ClassParsingClientRequest.hpp"

RP15::ClassParsingClientRequest( void ){}

void RP15::insert(const DATA &arg){
	parse_data.insert(parse_data.end(), arg.begin(), arg.end());
}

bool	RP15::is_ready( void ){
	if (parse_data.size() < 4)
		return (0);
	if (*((parse_data.end() - 1)) == '\n' && *((parse_data.end() - 2)) == '\r' && *((parse_data.end() - 3)) == '\n')
		return (1);
	return (0);
}
RP15::ClassParsingClientRequest(const RP15 &arg){
	parse_data = arg.parse_data;
	method = arg.method;
	ressource = arg.ressource;
	protocol = arg.protocol;
	host = arg.host;
	connection = arg.connection;
	sec_ch_ua = arg.sec_ch_ua;
	sec_ch_ua_mobile = arg.sec_ch_ua_mobile;
	user_agent = arg.sec_ch_ua_mobile;
	sec_ch_ua_platform = arg.sec_ch_ua_platform;
	accept = arg.accept;
	sec_fetch_site = arg.sec_fetch_site;
	sec_fetch_mode = arg.sec_fetch_mode;
	sec_fetch_dest = arg.sec_fetch_dest;
	referer = arg.referer;
}
RP15	RP15::operator=(const RP15 &arg){
	parse_data = arg.parse_data;
	method = arg.method;
	ressource = arg.ressource;
	protocol = arg.protocol;
	host = arg.host;
	connection = arg.connection;
	sec_ch_ua = arg.sec_ch_ua;
	sec_ch_ua_mobile = arg.sec_ch_ua_mobile;
	user_agent = arg.sec_ch_ua_mobile;
	sec_ch_ua_platform = arg.sec_ch_ua_platform;
	accept = arg.accept;
	sec_fetch_site = arg.sec_fetch_site;
	sec_fetch_mode = arg.sec_fetch_mode;
	sec_fetch_dest = arg.sec_fetch_dest;
	referer = arg.referer;
	return (*this);
}


void	ClassParsingClientRequest::request_ready( void )
{
	DATA	tmp_data;
	size_t	line = 0;

	for(DATA::iterator it = parse_data.begin(); it != parse_data.end(); it++)
	{
		tmp_data.clear();
		for(; *it != '\n' && it != parse_data.end();it++)
			tmp_data.push_back(*it);
		if (!std::strncmp((char*)tmp_data.begin().base(), " ", 2))
			method.assign(tmp_data.begin(), tmp_data.end());
	}
}

bool	ClassParsingClientRequest::compare(std::vector<unsigned char>::const_iterator pos, const std::string &str)const
{
	for (unsigned int i = 0; str[i] != '\0'; i++)
	{
		if (*pos != str[i])
			return (0);
		pos++;
	}
	return (1);
}

ClassParsingClientRequest::~ClassParsingClientRequest(){};

std::ostream & operator<<(std::ostream & ostream, std::vector<unsigned char> const &i)
{
	for (std::vector<unsigned char>::const_iterator it = i.begin(); it != i.end(); it++)
		ostream << *it;
	return (ostream);
}

void	ClassParsingClientRequest::display_cpcr( void )
{
	std::cout << "method: "<< method << std::endl;
	std::cout << "ressource: " << ressource << std::endl;
	std::cout << "protocol: "<< protocol << std::endl;
	std::cout << "host: "<< host << std::endl;
	std::cout << "connection: "<< connection << std::endl;
	std::cout << "sec_ch_ua: "<< sec_ch_ua << std::endl;
	std::cout << "sec_ch_ua_mobile: "<< sec_ch_ua_mobile << std::endl;
	std::cout << "user_agent: "<< user_agent << std::endl;
	std::cout << "sec_ch_ua_platform: "<< sec_ch_ua_platform << std::endl;
	std::cout << "accept: "<< accept << std::endl;
	std::cout << "sec_fetch_site: "<< sec_fetch_site << std::endl;
	std::cout << "sec_fetch_mode: "<< sec_fetch_mode << std::endl;
	std::cout << "sec_fetch_dest: "<< sec_fetch_dest << std::endl;
	std::cout << "referer: "<< referer << std::endl;
	std::cout << "-----------------------------------------------------------\n"; 
}