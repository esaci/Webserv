#ifndef PARSER_HPP
# define PARSER_HPP

# include "P_server.hpp"

class Parser
{
    private:
        Parser(void);
        Parser(const Parser &);
        Parser  &operator=(const Parser &);
    public:
        Parser(std::fstream &);
        ~Parser();
        // data //
        _ERRORP     error_p;   // set default error; Context:	http, server, location, if in location  4 Setup des pages d’erreur par défaut
        size_t      size_cmb;  // client_max_boody;  Context:	http, server, location                  5 Limiter la taille du body des clients
        std::string root;      // Context:	http, server, location, if in location                      8 Définir un répertoire ou un fichier à partir duquel le fichier doit être recherché (par exemple si l’url /kapouet est rootée sur /tmp/www, l’url /kapouet/pouic/toto/pouet est /tmp/www/pouic/toto/pouet).
        bool        autoindex; // Context:	http, server, location                                      9 Activer ou désactiver le listing des répertoires
        bool        error;     // if error == 0; il n'y pas d'erreur;
        std::vector<P_server> serv;
        std::set<std::pair<std::string, int> >   tab_ap;

        _INDEX      index;    // http, server, location                                                 10 Set un fichier par défaut comme réponse si la requête est un répertoire.
        //  setter  //
        bool    set_error_page(std::string &line);
        bool    set_client_max_body(std::string &line);
        void    set_root(std::string &line);
        bool    set_autoindex(std::string &line);
        void    set_index(std::string &);

        // check some error //
        bool        check_error_bracket(bool, bool, bool) const;
        bool        check_error_bracket_end(bool &, bool &);
        std::string new_location(std::string &);
        bool        check_if_error_parsing(std::vector<P_server> &);

        
        std::set<std::pair<std::string, int> > get_all_addr_port(void);// getter pour avoir tous les hosts et port qui se situe dans un serveur;
};
#endif

// Informational responses  (100–199)
// Successful responses     (200–299)
// Redirection messages     (300–399)
// Client error responses   (400–499)
// Server error responses   (500–599)