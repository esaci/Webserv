#ifndef CLASSPARSINGCLIENTREQUEST_HPP
# define CLASSPARSINGCLIENTREQUEST_HPP

# include "w_defines.hpp"

// method ressource et protocole sont necessaire, le reste nexiste pas forcement

class RP15
{
	public:
		DATA	parse_data;
		DATA	method;
		DATA	ressource;
		DATA	protocol;
		DATA	host;
		DATA	connection;
		DATA	sec_ch_ua;
		DATA	sec_ch_ua_mobile;
		DATA	user_agent;
		DATA	sec_ch_ua_platform;
		DATA	accept;
		DATA	sec_fetch_site;
		DATA	sec_fetch_mode;
		DATA	sec_fetch_dest;
		DATA	referer;

	public:
		RP15( void );
		~RP15();
		bool	compare(DATA::const_iterator , const std::string &)const;
		void	parse_request_line(DATA &arg);
		void	request_ready( void );
		bool	is_ready( void );
		void	display_cpcr( void );
		void	insert(const DATA &arg);
		RP15	(const RP15&);
		RP15	operator=(const RP15 &);
	private:
		ClassParsingClientRequest(const DATA &arg);
};

std::ostream & operator<<(std::ostream & ostream, DATA const &i);

#endif