#include "../include/w_library.hpp"
#include "../include/ClassParsingClientRequest.hpp"

ClassParsingClientRequest::ClassParsingClientRequest(const std::vector<unsigned char> &arg)
{
	unsigned int i = 0;
	unsigned int y = 0;

	if  (!arg.size())
		return ;
	for (std::vector<unsigned char>::const_iterator it = arg.begin(); it != arg.end(); it++)
	{
		if (i == 0)
		{
			while (*it != ' ')
			{
				method.push_back(*(it));
				it++;
			}
			it++;
			while (*it != ' ')
			{
				ressource.push_back(*(it));
				it++;
			}
			it++;
			while (*it != ' ' && *it != '\n')
			{
				protocol.push_back(*(it));
				it++;
			}
		}
		if (y == 0 && compare(it, "Host:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				host.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "Connection:"))
		{
		   while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				connection.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "sec-ch-ua:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				sec_ch_ua.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "sec-ch-ua-mobile:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				sec_ch_ua_mobile.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "User-Agent:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				user_agent.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "sec-ch-ua-platform:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				sec_ch_ua_platform.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "Accept:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				accept.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "Sec-Fetch-Site:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				sec_fetch_site.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "Sec-Fetch-Mode:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				sec_fetch_mode.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "Sec-Fetch-Dest:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				sec_fetch_dest.push_back(*it);
				it++;
			}
		}
		else if (y == 0 && compare(it, "Referer:"))
		{
			while (*it != ' ')
				it++;
			it++;
			while (*it != '\n')
			{
				referer.push_back(*it);
				it++;
			}
		}
		y++;
		if (*it == '\n')
		{
			y = 0;
			i++;
		}
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