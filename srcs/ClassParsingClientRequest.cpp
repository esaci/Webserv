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

size_t	until_space(DATA::iterator	it){
	size_t			res;
	unsigned char	*tmp_c = it.base();

	if (!tmp_c)
		return (0);
	for (res = 0; tmp_c && tmp_c[res] && tmp_c[res] != ' '; res++)
		;
	return (res);
}

size_t	until_no_space(DATA::iterator it){
	size_t			res;
	unsigned char	*tmp_c = it.base();

	if (!tmp_c)
		return (0);
	for (res = 0; tmp_c && tmp_c[res] && tmp_c[res] == ' '; res++)
		;
	return (res);
}

void	ClassParsingClientRequest::parse_request_line(DATA &arg){
	size_t	pos_method;
	size_t	pos_ressource;
	// size_t	pos_protocol;
	
	pos_method = until_space(arg.begin());

	// pos_ressource += pos_method;
	// pos_protocol += pos_ressource;
	method.assign(arg.begin(), arg.begin() + pos_method);
	pos_method += until_no_space(arg.begin() + pos_method);
	pos_ressource = until_space(arg.begin() + pos_method);
	ressource.assign(arg.begin() + pos_method, arg.begin() + pos_ressource + pos_method);
	// pos_protocol = until_space(arg.begin() + pos_ressource + until_no_space(arg.begin() + pos_ressource));
	// protocol.assign(arg.begin() + pos_ressource + until_no_space(arg.begin() + pos_ressource), arg.begin() + pos_protocol);
}

void	ClassParsingClientRequest::request_ready( void )
{
	std::cout << parse_data;
	std::cout << "-------------------------------------------------------------------\n";
	DATA	tmp_data, tmp_compare;
	size_t	line = 0, i = 0;
	std::vector<DATA>	tab;
	tab.push_back(_data_init("Host: "));
	tab.push_back(_data_init("Connection: "));
	tab.push_back(_data_init("Cache-Control: "));
	tab.push_back(_data_init("sec-ch-ua: "));
	tab.push_back(_data_init("sec-ch-ua-mobile: "));
	tab.push_back(_data_init("sec-ch-ua-platform: "));
	tab.push_back(_data_init("Upgrade-Insecure-Requests: "));
	tab.push_back(_data_init("User-Agent: "));
	tab.push_back(_data_init("Accept: "));
	tab.push_back(_data_init("Sec-Fetch-Site: "));
	tab.push_back(_data_init("Sec-Fetch-Mode: "));
	tab.push_back(_data_init("Sec-Fetch-User: "));
	tab.push_back(_data_init("Sec-Fetch-Dest: "));
	tab.push_back(_data_init("Accept-Encoding: "));
	tab.push_back(_data_init("Accept-Language: "));
	for(DATA::iterator it = parse_data.begin(); it != parse_data.end(); it++, line++)
	{
		tmp_data.clear();
		for(; *it != '\n' && it != parse_data.end(); it++)
		{
			if (*it == '\r')
				break;
			tmp_data.push_back(*it);
		}
		if (!line)
			parse_request_line(tmp_data);
		else{
			for(i = 0; i < tab.size(); i++)
			{
				if (tmp_data.size() >= tab[i].size())
				{
					tmp_compare.assign(tmp_data.begin(), tmp_data.begin() + tab[i].size());
					if (tab[i] == tmp_compare)
						break;
				}
			}
			switch (i)
			{
				case 0:
					host.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 1:
					connection.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 2:
					cache_control.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 3:
					sec_ch_ua.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 4:
					sec_ch_ua_mobile.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 5:
					sec_ch_ua_platform.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 6:
					upgrade_insecure_requests.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 7:
					user_agent.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 8:
					accept.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 9:
					sec_fetch_site.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 10:
					sec_fetch_mode.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 11:
					sec_fetch_dest.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 12:
					accept_encoding.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				case 13:
					accept_language.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
					break;
				//  case x:
				//    referer.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
				//    break;
				default:
					break;
			}
		}
	}
	display_cpcr();
	(void)tab;	
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
	std::cout << "method: |"<< method << "|" << std::endl;
	std::cout << "ressource: |" << ressource << "|" << std::endl;
	std::cout << "protocol: |"<< protocol << "|" << std::endl;
	std::cout << "host: |"<< host << "|" << std::endl;
	std::cout << "connection: |"<< connection << "|" << std::endl;
	std::cout << "Cache-Control: |"<< cache_control << "|" << std::endl;
	std::cout << "sec_ch_ua: |"<< sec_ch_ua << "|" << std::endl;
	std::cout << "sec_ch_ua_mobile: |"<< sec_ch_ua_mobile << "|" << std::endl;
	std::cout << "user_agent: |"<< user_agent << "|" << std::endl;
	std::cout << "sec_ch_ua_platform: |"<< sec_ch_ua_platform << "|" << std::endl;
	std::cout << "Upgrade-Insecure-Requests: |" << upgrade_insecure_requests << "|" << std::endl;
	std::cout << "accept: |"<< accept << "|" << std::endl;
	std::cout << "sec_fetch_site: |"<< sec_fetch_site << "|" << std::endl;
	std::cout << "sec_fetch_mode: |"<< sec_fetch_mode << "|" << std::endl;
	std::cout << "sec_fetch_dest: |"<< sec_fetch_dest << "|" << std::endl;
	std::cout << "Accept-Encoding: |"<< accept_encoding << "|" << std::endl;
	std::cout << "Accept-Language: |"<< accept_language << "|" << std::endl;
	std::cout << "-----------------------------------------------------------\n"; 
}