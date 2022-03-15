#ifndef CLASSPARSINGCLIENTREQUEST_HPP
# define CLASSPARSINGCLIENTREQUEST_HPP

# include "w_library.hpp"

class ClassParsingClientRequest
{
    public:
        std::vector<unsigned char> method;
        std::vector<unsigned char> ressource;
        std::vector<unsigned char> protocol;
        std::vector<unsigned char> host;
        std::vector<unsigned char> connection;
        std::vector<unsigned char> sec_ch_ua;
        std::vector<unsigned char> sec_ch_ua_mobile;
        std::vector<unsigned char> user_agent;
        std::vector<unsigned char> sec_ch_ua_platform;
        std::vector<unsigned char> accept;
        std::vector<unsigned char> sec_fetch_site;
        std::vector<unsigned char> sec_fetch_mode;
        std::vector<unsigned char> sec_fetch_dest;
        std::vector<unsigned char> referer;


    public:
        ClassParsingClientRequest(const std::vector<unsigned char> &);
        bool    compare(std::vector<unsigned char>::const_iterator , const std::string &)const;
        ~ClassParsingClientRequest();
		void	display_cpcr( void );
};

std::ostream & operator<<(std::ostream & ostream, std::vector<unsigned char> const &i);

#endif