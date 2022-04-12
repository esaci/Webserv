#ifndef CLASSPARSINGCLIENTREQUEST_HPP
# define CLASSPARSINGCLIENTREQUEST_HPP

# include "w_defines.hpp"

class server_data;
// method ressource et protocole sont necessaire, le reste ne le sont pas forcement
// responding:	   0 au depart, 
				// 1 lorsque le l'entity a ete remplis(fin de requete pour GET, debut de parsing du body pour POST) et on s'apprete a appliquer la requete
				// 2 lorsque la ressource a ete ouverte (_get_response) et on s'apprete a la lire
				// 3 lorsque la ressource a ete lu completement et ecrite dans r_buffer et on s'apprete a ajouter l'entity au r_buffer
				// 4 l'entity a ete ajoute a r_buffer(buffer de reponse) et on est en train d'envoyer la response
class RP15
{
	public:
		int			responding;
		int			return_error;
		bool		r_l_v;
		int			serverfd;
		size_t		last_size, last_step, last_remove;
		std::time_t	time_client;
		DATA		redirection;
		DATA		r_buffer;
		DATA		r_body_get;
		DATA		r_body_buffer;
		DATA		parse_data;
		DATA		method;
		DATA		ressource;
		DATA		u_ressource;
		DATA		protocol;
		DATA		host;
		DATA		cache_control;
		DATA		connection;
		DATA		sec_ch_ua;
		DATA		sec_ch_ua_mobile;
		DATA		sec_ch_ua_platform;
		DATA		upgrade_insecure_requests;
		DATA		user_agent;
		DATA		accept;
		DATA		sec_fetch_site;
		DATA		sec_fetch_mode;
		DATA		sec_fetch_dest;
		DATA		accept_encoding;
		DATA		accept_language;
		DATA		referer;
		DATA		content_length;
		DATA		content_type;
		DATA		transfer_encoding;
		DATA		tmp_data;
		DATA		tmp_compare;
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
		int		fill_request(int code, std::vector<struct pollfd>::iterator it);
		int		basic_cgi(server_data *s, int fd);
		int	set_cgi_env(server_data *s, int fd);
		int		_set_folder(DIR	*folder, std::string &root, bool index);
		void	_set_info(size_t len, std::string &tmp_s, struct dirent *tmp_f, std::string &root);
		int		_post_first_body(DATA::iterator it);
		int		_delete_number( void );
		int		_post_cgi(server_data *d_s, int clientfd);
		int		_time_init( void );
		int		delete_request(server_data *d_s, int clientfd);
		bool	_cgi_extensions( void );
	private:
		RP15	(const DATA &arg);
		char 	**ev;
};

std::ostream & operator<<(std::ostream & ostream, DATA const &i);

#endif