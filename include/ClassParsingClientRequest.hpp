#ifndef CLASSPARSINGCLIENTREQUEST_HPP
# define CLASSPARSINGCLIENTREQUEST_HPP

# include "w_defines.hpp"


// method ressource et protocole sont necessaire, le reste ne le sont pas forcement
// responding:	   0 au depart, 
				// 1 lorsque le l'entity a ete remplis(fin de requete pour GET, debut de parsing du body pour POST) et on s'apprete a appliquer la requete
				// 2 lorsque la ressource a ete ouverte (_get_response) et on s'apprete a la lire
				// 3 lorsque la ressource a ete lu completement et ecrite dans r_buffer et on s'apprete a ajouter l'entity au r_buffer
				// 4 l'entity a ete ajoute a r_buffer(buffer de reponse) et on est en train d'envoyer la response
class RP15
{
	public:
		int		responding;
		int		return_error;
		bool	r_l_v;
		DATA	redirection;
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
		DATA	tmp_data;
		DATA	tmp_compare;
	public:
		RP15	( void );
		~RP15	( void );
		RP15	(const RP15&);
		RP15	operator=(const RP15 &);
		void	parse_request_line(DATA &arg);
		void	clear_ressource( void );
		int		request_ready( void );
		bool	is_ready( void );
		size_t	extract_body_check( void );
		void	display_cpcr( void );
		int		fill_request(int code);
		int		_set_folder(DIR	*folder);
		void	_set_info(size_t len, std::string &tmp_s, struct dirent *tmp_f);
	private:
		RP15	(const DATA &arg);
};

std::ostream & operator<<(std::ostream & ostream, DATA const &i);

#endif