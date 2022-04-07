#ifndef SERVER_DATA_HPP
# define SERVER_DATA_HPP

#	include "w_defines.hpp"
#	include "P_server.hpp"
// Modif Fichier de config
// serverfd va etre un set_serverfd
	// ca proc new_client que si il fait parti du set
// listening deviendra un tableau de bool, chacun initialise a 0,
	// Listen proc par chac bool
// un meme client peut faire des requetes sur deux port different, auront ils deux fd differents (jespere que oui)
// il faudra lier le client avec son server, 
	// map<int, int> lien entre client et server , clients_to_servers

	class server_data{
		public:
			//	donner que raph vient d'ajouter
			std::set<std::pair<std::string, int> >					tab_ap;      // pair address, port;
			std::set<std::pair<std::pair<std::string, int>, int> >	tab_tab_ap;	 // pair pair addres, port, numero serv;	
			//////////////////////////////////////
			std::vector<P_server>		servs_conf;
			bool						error_conf; // savoir si il y a une erreur dans le fichier .conf
			C_DATA						codes;
			CT_DATA						ctypes;
			R_DATA						tab_request;
			std::map<int, int>			files_to_clients;
			std::vector<struct pollfd>	tab_poll;
			int							serverfd;
			size_t						pos;
			bool						listening;
//			VARIABLES MODIFIES REGULIEREMENT
			std::time_t					time_server;
			struct pollfd				client_poll;
			DATA						recvline;
		public:
			server_data(std::fstream &file);
			~server_data( void );
			std::string						display_code(int n_code);
			int								_server( void );
			int								_server_read(std::vector<struct pollfd>::iterator it);
			int								handle_line_request(std::vector<struct pollfd>::iterator it, size_t n);
			int								_new_client(std::vector<struct pollfd>::iterator it);
			int								_read_client(std::vector<pollfd>::iterator it);
			int								_post_server_read(std::vector<pollfd>::iterator it);
			int								_post_read_cl(std::vector<pollfd>::iterator it);
			int								_post_read_ch(std::vector<pollfd>::iterator it);
			int								_response(int clientfd);
			void							_code_init( void );
			void							_content_type( void );
			void							_table_poll_init( void );
			int								_get_index(int clientfd);
			int								_get(int clientfd);
			int								_get_error(int clientfd);
			int								_get_error_400(int clientfd);
			int								_get_error_404(int clientfd);
			int								_get_error_408(int clientfd);
			int								_get_error_403(int clientfd);
			void							_entity(int code_n, int clientfd);
			void							_entity_no_accept(int code_n, int clientfd);
			std::string						_entity_ctype(int clientfd);
			int								_send(int client, int code);
			int								setup_listen(std::vector<struct pollfd>::iterator it);
			int								setup_read(std::vector<struct pollfd>::iterator it);
			int								setup_response(std::vector<struct pollfd>::iterator it);
			int								setup_read_files(std::vector<struct pollfd>::iterator it);
			int								_set_file(int clientfd);
			int								_time_maj( void );
			int								_time_stop_client(std::vector<struct pollfd>::iterator it);
			int								delete_request(int clientfd);

		private:
			server_data( void );
			server_data(const server_data&);
			server_data						&operator=(const server_data&);
	};

#endif