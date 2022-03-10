#ifndef P_CONF_HPP
# define P_CONF_HPP

#	include <iostream>

class	p_conf{
		public:
			DATA		port;
			DATA		root;
			DATA		index;
			DATA		server_name;
			DATA		location;
			bool		location_auto_index;

		private:
			p_conf(){}
			p_conf(const p_conf &){}
		public:
			p_conf(std::fstream &file);
			~p_conf( void );

	};

#endif