#ifndef SERVER_DATA_HPP
# define SERVER_DATA_HPP

#	include "w_defines.hpp"

	class server_data{
		public:
			C_DATA *codes;
			CT_DATA *ctypes;
			p_conf *conf;
		public:
			server_data(std::fstream &file);
			~server_data( void );
			std::string		display_code(int n_code);
			int				_server( void );
			int				_response(R_DATA p, int connfd);
			void			_code_init( void );
			void			_content_type( void );
			int				_get_index(int clientfd);
			int				_get_favicon(int clientfd);
			int				_get_error_400(int clientfd);
			int				_get_error_404(int clientfd);
			void			_entity(DATA &buff, int code_n, std::string content_type);
			void			_entity_no_accept(DATA &buff, int code_n, std::string content_type);
		private:
			server_data( void );
			server_data(const server_data&);
			server_data &operator=(const server_data&);
	};

#endif