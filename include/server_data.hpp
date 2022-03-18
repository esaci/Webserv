#ifndef SERVER_DATA_HPP
# define SERVER_DATA_HPP

#	include "w_defines.hpp"

	class server_data{
		public:
			C_DATA						codes;
			CT_DATA						ctypes;
			p_conf						conf;
			R_DATA						tab_request;
			int							serverfd;
//			VARIABLES MODIFIES REGULIEREMENT
			std::vector<struct pollfd>	tab_poll;
			DATA						recvline;
			std::vector<char>			char_buff;
			DATA						parse_temp;
		public:
			server_data(std::fstream &file);
			~server_data( void );
			std::string		display_code(int n_code);
			int				_server( void );
			int				_server_read(std::vector<struct pollfd>::iterator it);
			int				_new_client(std::vector<struct pollfd>::iterator it);
			int				_read_client(std::vector<pollfd>::iterator it);
			int				_response(int clientfd);
			void			_code_init( void );
			void			_content_type( void );
			void			_table_poll_init( void );
			int				_get_index(int clientfd);
			int				_get_favicon(int clientfd);
			int				_get_error_400(int clientfd);
			int				_get_error_404(int clientfd);
			void			_entity(int code_n, std::string content_type);
			void			_entity_no_accept(int code_n, std::string content_type);
			std::string		_entity_ctype(int clientfd);
		private:
			server_data( void );
			server_data(const server_data&);
			server_data		&operator=(const server_data&);
	};

#endif