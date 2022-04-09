#ifndef P_SERVER_HPP
# define P_SERVER_HPP

# include <iostream>
# include <vector>
# include <set>
# include <map>
# include <fstream>
# include <cstdlib>
# include <cctype>
# include <arpa/inet.h>
# include <sstream>
# include <utility>

# include "w_defines.hpp"

class P_server
{
    private:
        
    public:
        P_server();
        P_server(const P_server &);
        P_server    &operator=(const P_server &);
        ~P_server();
        // data //
        std::string     s_name;         //Context:	server                                      2 Setup server_names ou pas.
        _MAP_ERRORP     map_error_p;    // Context:	http, server, location, if in location      4 Setup des pages d’erreur par défaut
        _CMBS           map_size_cmb;   // client_max_boody;  Context:	http, server, location  5 Limiter la taille du body des clients
        _MAP_ROOT       map_root;       // Context:	http, server, location, if in location      8 Définir un répertoire ou un fichier à partir duquel le fichier doit être recherché (par exemple si l’url /kapouet est rootée sur /tmp/www, l’url /kapouet/pouic/toto/pouet est /tmp/www/pouic/toto/pouet).
        _MAP_AUTO_I     map_autoindex;  // Context:	http, server, location                      9 Activer ou désactiver le listing des répertoires
        _MAP_ADDR_PORT  tab_addr_port;  // listen; Context: server                              1 Choisir le port et l’host de chaque "serveur".  3 (pas sur d'avoir saisit) Le premier serveur pour un host:port sera le serveur par défaut pour cet host:port (ce qui signifie qu’il répondra à toutes les requêtes qui n’appartiennent pas à un autre serveur)
        _MAP_INDEX      map_index;      // http, server, location                               10 Set un fichier par défaut comme réponse si la requête est un répertoire.
        _MAP_L_EXEPT    map_limit_exept;// Context:	location                                    6 Définir une liste de méthodes HTTP acceptées pour la route.
        _MAP_CGI_EXT    map_cgi_ext;    // context: location pour l'instant : sert a voir l'enssemble des extntion que le cgi peut executer a l'interieur d'une location;
        _MAP_CGI_DIR    map_cgi_dir;    // context: location pour l'instant : l'endroit ou est executer le cgi; 
        _MAP_REDIRECT   map_redirect;   // context: server location;                            7 Définir une redirection HTTP.
        std::string     path_upload_dir; // context: server upload;


        std::set<std::pair<std::string, int> >                   tab_ap;
        // std::vector<P_location> loc; // tab class location;
        // // setter //
        bool    set_error_page(std::string &, std::string &);
        bool    set_client_max_body(std::string &, std::string &);
        void    set_root(std::string &, std::string &);
        bool    set_autoindex(std::string &, std::string &);
        bool    set_new_port(std::string &);
        void    set_index(std::string &, std::string &);
        void    set_s_name(std::string &);
        bool    set_limit_exept(std::string &, std::string &);
        void    set_cgi_ext(std::string &, std::string &);
        void    set_cgi_dir(std::string &, std::string &);
        bool    set_redirect(std::string &, std::string &);
        bool    set_path_upload_dir(std::string &);

        // getter pour different elements //
        // pas besoin pour le server name car il est le meme pour tout le server du coup il faut juste aller le chercher dans sa string.
        std::string                 get_root(std::string); // envoie la location et retourne le root en fonction de la location. si la location n'existe pas envoie le root par default. ou envoie le root "\";
        std::string                 get_error_page(std::string, int); // envoie la location et le code d'erreur. renvoie la page a afficher.
        bool                        get_autoindex(std::string); // envoie la location et renvoie si l'autoindex est 0 ou 1;
        size_t                      get_client_max_body(std::string); // envoie la location et renvoie le client_max_body en fonction de la location;
        std::vector<std::string>    get_addresses(int port);  // envoie le port et renvoie les addresses du port sur lequelle il ecoute;
        std::vector<std::string>    get_all_index(std::string); // envoie la location et renvoie tous les index indiquer en fonction de la localisation; 
};

std::string get_root(std::vector<P_server>, std::string, std::pair<std::string, int>, std::string);

#endif