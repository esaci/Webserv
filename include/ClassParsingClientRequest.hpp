#ifndef CLASSPARSINGCLIENTREQUEST_HPP
# define CLASSPARSINGCLIENTREQUEST_HPP

# include "w_defines.hpp"

// method ressource et protocole sont necessaire, le reste ne le sont pas forcement

class RP15
{
	public:
		int		responding;
		DATA	r_buffer;
		DATA	r_body_buffer;
		DATA	parse_data;
		DATA	method;
		DATA	ressource;
		DATA	protocol;
		DATA	host;
		DATA	cache_control;
		DATA	connection;
		DATA	sec_ch_ua;
		DATA	sec_ch_ua_mobile;
		DATA	sec_ch_ua_platform;
		DATA	upgrade_insecure_requests;
		DATA	user_agent;
		DATA	accept;
		DATA	sec_fetch_site;
		DATA	sec_fetch_mode;
		DATA	sec_fetch_dest;
		DATA	accept_encoding;
		DATA	accept_language;
		DATA	referer;
		DATA	content_length;
		DATA	transfer_encoding;

	public:
		RP15	( void );
		~RP15	( void );
		RP15	(const RP15&);
		RP15	operator=(const RP15 &);
		void	parse_request_line(DATA &arg);
		void	request_ready( void );
		bool	is_ready( void );
		size_t	extract_body_check( void );
		void	display_cpcr( void );
		void	insert(const DATA &arg);
	private:
		RP15	(const DATA &arg);
};

std::ostream & operator<<(std::ostream & ostream, DATA const &i);

#endif