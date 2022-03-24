#ifndef SERVER_DATA_HPP
# define SERVER_DATA_HPP

#	include "w_defines.hpp"

	class server_data{
		public:
			C_DATA						codes;
			CT_DATA						ctypes;
			R_DATA						tab_request;
			std::map<int, int>			files_to_socket;
			int							serverfd;
//			VARIABLES MODIFIES REGULIEREMENT
			struct pollfd				client_poll;
			std::vector<struct pollfd>	tab_poll;
			DATA						recvline;
			std::vector<char>			char_buff;
			DATA						read_temp;
			bool						listening;
			size_t						pos;
			// Ca va etre bientot suppr
			p_conf						conf;
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
			int				_get(int clientfd);
			int				_get_error_400(int clientfd);
			int				_get_error_404(int clientfd);
			void			_entity(int code_n, int clientfd);
			void			_entity_no_accept(int code_n, int clientfd);
			std::string		_entity_ctype(int clientfd);
			int				_send(int client, int code);
			int				setup_listen(std::vector<struct pollfd>::iterator it);
			int				setup_read(std::vector<struct pollfd>::iterator it);
			int				setup_response(std::vector<struct pollfd>::iterator it);
			int				setup_read_files(std::vector<struct pollfd>::iterator it);
			int				_set_file(int clientfd);
		private:
			server_data( void );
			server_data(const server_data&);
			server_data		&operator=(const server_data&);
	};

#endif