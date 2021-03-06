#include "../include/Parser.hpp"

//////////////////////////////////////////////////////////////////
//  La class Parser vas parser l'enssemble du fichier et renvoyer les differentes infos dans un tableau de classe serveur
//  Quelques gestion d'erreur se fait aussi a l'interieur si une erreur se produit alors le parsing s'arrete et renvoie une erreur.
//  Le fichier parser est un fichier de type nginx. et donc le parsing en est inspirer (mais ce n'est pas le meme).
/////////////////////////////////////////////////////////////////
Parser::Parser(std::fstream &file)  // constructeur de la classe Parser avec un fichier comme argument.
{
    this->error = 0;    // variable qui servira plus tard si une erreur est intervenue lors du parsing.
    std::string line;   // string qui permet d'avoir chaque ligne du fichier
    bool    in_s = 0;   // pour savoir si je suis dans une directive de block server
    bool    in_l = 0;   // pour savoir si je suis dans une directive de block location
    std::string loc = ""; // me sert a la location par defaut;
    this->size_cmb = 1; // sera la size par defaut de la variable size_cmb qui est le client_max_boody;
    // ajout des pages d'erreur de client et de serveur par defaut
    // client error responses //
    this->error_p[100]  = "./files_system/Continue.html";
    this->error_p[200]  = "./files_system/Ok.html";
    this->error_p[301] = "./files_system/Moved_Permanently.html";
    this->error_p[400] = "./files_system/Bad_Request.html";
    this->error_p[401] = "./files_system/Unauthorized.html";
    this->error_p[402] = "./files_system/Payment_required";
    this->error_p[403] = "./files_system/Forbidden.html";
    this->error_p[404] = "./files_system/Not_Found.html";
    this->error_p[405] = "./files_system/Not_allowed.html";
    this->error_p[406] = "./files_system/Not_acceptable";
    this->error_p[407] = "./files_system/Proxy_authentication_required.html";
    this->error_p[408] = "./files_system/Request_Timeout.html";
    this->error_p[409] = "./files_system/Conflict.html";
    this->error_p[410] = "./files_system/Gone.html";
    this->error_p[411] = "./files_system/Length_required.html";
    this->error_p[412] = "./files_system/Precondition_failed.html";
    this->error_p[413] = "./files_system/Payload_too_large.html";
    this->error_p[414] = "./files_system/Uri_too_long.html";
    this->error_p[415] = "./files_system/Unsupported_media_type.html";
    this->error_p[416] = "./files_system/Range_not_satisfiable.html";
    this->error_p[417] = "./files_system/Expectation_failed.html";
    this->error_p[418] = "./files_system/I_m_a_teapot.html";
    this->error_p[421] = "./files_system/Misdirected_request.html";
    this->error_p[422] = "./files_system/Unprocessable_entity.html";
    this->error_p[423] = "./files_system/Locked.html";
    this->error_p[424] = "./files_system/Failed_dependency.html";
    this->error_p[425] = "./files_system/Too_early.html";
    this->error_p[426] = "./files_system/Upgrade_required.html";
    this->error_p[428] = "./files_system/Precondition_required.html";
    this->error_p[429] = "./files_system/Too_many_requests.html";
    this->error_p[431] = "./files_system/Request_header_fields_too_large.html";
    this->error_p[451] = "./files_system/Unavailable_for_legal_reasons.html";

    //Server error responses
    this->error_p[500] = "./files_system/Internal_server_error.html";
    this->error_p[501] = "./files_system/Not_implemented.html";
    this->error_p[502] = "./files_system/Bad_gateway.html";
    this->error_p[503] = "./files_system/Service_unavailable.html";
    this->error_p[504] = "./files_system/Gateway_timeout.html";
    this->error_p[505] = "./files_system/Http_version_not_supported.html";
    this->error_p[506] = "./files_system/Variant_also_negotiates.html";
    this->error_p[507] = "./files_system/Insufficient_storage.html";
    this->error_p[508] = "./files_system/Loop_detected.html";
    this->error_p[510] = "./files_system/Not_extended.html";
    this->error_p[511] = "./files_system/Network_authentication_required.html";

    // autoindex by default //
    this->autoindex = 0;
    /////////////////////////

    //////////////////////////////////////////////////////////////////
    while (std::getline(file, line)) // temp qu il y a des lignes dans le fichier.
    {
        int     i = 0; // sert a enlever les premiers ' ' ainsi que tab horizontal de chaque ligne
        for (; line[i] == ' ' || line[i] == 9; i++){} // iteration sur toute la ligne jusqu'a qu'il y est plus d'espace et de '\t'
        line = line.substr(i);   // ligne prend la valeur de ligne a partir de la position de i;                     
        if (line.length() > 0 && line[0] != '#') // si la taille de ligne est superieur a 0 et le priemier charactere de la ligne est '#' rentrer dans la fonction  
        {
            if (!((*(line.end() - 1) == ';' || *(line.end() - 1) == '{' || *(line.end() - 1) == '}'))) // si la fin de la ligne est ';' ou '{' ou '}' renvoyer une erreur et arreter le programme
            {
                _ERR_FILE;       // le fichier renvoie une erreur 
                this->error = 1;
                return;
            }
            if (line == "server {")
            {
                if (check_error_bracket(in_s, in_l, 0) == 1) return ;
                in_s = 1;
                P_server    lala;
                _ERRORP     lala2;
                loc = "";
                 std::vector<std::string> lala3;
                this->serv.push_back(lala);
                this->serv[this->serv.size() - 1].map_error_p[loc] = this->error_p;
                this->serv[this->serv.size() - 1].map_size_cmb[loc] = this->size_cmb;
                this->serv[this->serv.size() - 1].map_root[loc] = this->root;
                this->serv[this->serv.size() - 1].map_limit_exept[loc] = lala3;
                this->serv[this->serv.size() - 1].map_autoindex[loc] = this->autoindex;
                this->serv[this->serv.size() - 1].map_index[loc] = this->index;
                continue;
            }
            if (line.compare(0, 9,"location ") == 0 && (*(line.end() - 1)) == '{')
            {
                if (check_error_bracket(in_s, in_l, 1) == 1) return ;
                in_l = 1;
                loc = this->new_location(line);
                if (loc.size() > 1 && *(loc.end() - 1) != '/')
                    loc.append("/");
                // faire une verif si le loc est ok
                this->serv[this->serv.size() - 1].map_error_p[loc] = this->serv[this->serv.size() - 1].map_error_p[""];
                this->serv[this->serv.size() - 1].map_size_cmb[loc] = this->serv[this->serv.size() - 1].map_size_cmb[""];
                this->serv[this->serv.size() - 1].map_root[loc] = this->serv[this->serv.size() - 1].map_root[""];
                this->serv[this->serv.size() - 1].map_limit_exept[loc] = this->serv[this->serv.size() - 1].map_limit_exept[""];
                this->serv[this->serv.size() - 1].map_autoindex[loc] = this->serv[this->serv.size() - 1].map_autoindex[""];
                this->serv[this->serv.size() - 1].map_index[loc] = this->serv[this->serv.size() - 1].map_index[""];
                continue;
            }
            if (line == "}")
            {
                loc = "";
                if (check_error_bracket_end(in_s, in_l) == 1)
                    return ;
                continue;
            }
            if (line.compare(0,7, "listen ") == 0 && in_s == 1 && in_l == 0)
            {
                if (this->serv[this->serv.size() - 1].set_new_port(line) == 1)
                {
                    std::cerr << "\e[0;31m" << "listen is not well configured exemple: listen 127.0.0.1:80;" << "\e[0m"<< std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 12, "server_name ") == 0 && in_s == 1 && in_l == 0)
            {
                this->serv[this->serv.size() - 1].set_s_name(line);
                continue;
            }
            if (line.compare(0, 11, "error_page ") == 0 && in_s == 0)
            {
                if (this->serv.size() > 0)
                {
                    std::cerr << "\e[0;31m" << line << "\e[0m" << std::endl;
                    std::cerr << "\e[0;31m" << "error_page not well configured: the info has to be before the context serv;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                if (this->set_error_page(line) == 1)
                {
                    std::cerr << "\e[0;31m" << "error page not well configured exemple: error_page 404 www/error_page_404.html;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 11, "error_page ") == 0 && in_s == 1)
            {
                if (loc == "" && this->serv[this->serv.size() - 1].map_error_p.size() > 1)
                {
                    std::cerr << "\e[0;31m" << "error can't put page after in server after a location" << "\e[0m" << std::endl;
                    this->error = 1;
                    return;
                }
                if (this->serv[this->serv.size() - 1].set_error_page(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "error page not well configured exemple: error_page 404 www/error_page_404.html;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 21, "client_max_body_size ") == 0 && in_s == 0)
            {
                if (this->serv.size() > 0)
                {
                    std::cerr << "\e[0;31m" << line << "\e[0m" << std::endl;
                    std::cerr << "\e[0;31m" << "client_max_body_size not well configured: the info has to be before the context serv;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                if (this->set_client_max_body(line) == 1)
                {
                    std::cerr << "\e[0;31m" << "client_max_body_size not well configured exemple: client_max_body_size 100;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 21, "client_max_body_size ") == 0 && in_s == 1)
            {
                if (loc == "" && this->serv[this->serv.size() - 1].map_size_cmb.size() > 1)
                {
                    std::cerr << "\e[0;31m" << "error write in server after a location" << "\e[0m" << std::endl;
                    this->error = 1;
                    return;
                }
                if (this->serv[this->serv.size() - 1].set_client_max_body(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "client_max_body_size not well configured exemple: client_max_body_size 100;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 5, "root ") == 0 && in_s == 0)
            {
                if (this->serv.size() > 0)
                {
                    std::cerr << "\e[0;31m" << line << "\e[0m" << std::endl;
                    std::cerr << "\e[0;31m" << "root not well configured: the info has to be before the context serv;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                this->set_root(line);
                continue;
            }
            if (line.compare(0, 5, "root ") == 0 && in_s == 1)
            {
                if (loc == "" && this->serv[this->serv.size() - 1].map_root.size() > 1)
                {
                    std::cerr << "\e[0;31m" << "error write in server after a location" << "\e[0m" << std::endl;
                    this->error = 1;
                    return;
                }
                this->serv[this->serv.size() - 1].set_root(line, loc);
                continue;
            }
            if (line.compare(0, 13, "limit_except ") == 0 && in_s == 1 && in_l == 1)
            {
                if (this->serv[this->serv.size() - 1].set_limit_exept(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "limit_except not well configured limit_except GET POST DELETE;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 10, "autoindex ") == 0 && in_s == 0)
            {
                if (this->serv.size() > 0)
                {
                    std::cerr << "\e[0;31m" << line << "\e[0m" << std::endl;
                    std::cerr << "\e[0;31m" << "autoindex not well configured: the info has to be before the context serv;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                if (this->set_autoindex(line) == 1)
                {
                    std::cerr << "\e[0;31m" << "autoindex not well configured exemple: autoindex off;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 10, "autoindex ") == 0 && in_s == 1)
            {
                if (loc == "" && this->serv[this->serv.size() - 1].map_autoindex.size() > 1)
                {
                    std::cerr << "\e[0;31m" << "error write in server after a location" << "\e[0m" << std::endl;
                    this->error = 1;
                    return;
                }
                if (this->serv[this->serv.size() - 1].set_autoindex(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "autoindex not well configured exemple: autoindex off;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 6, "index ") == 0 && in_s == 0)
            {
                if (this->serv.size() > 0)
                {
                    std::cerr << "\e[0;31m" << line << "\e[0m" << std::endl;
                    std::cerr << "\e[0;31m" << "index not well configured: the info has to be before the context serv;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                this->set_index(line);
                continue;
            }
            if (line.compare(0, 6, "index ") == 0 && in_s == 1)
            {
                if (loc == "" && this->serv[this->serv.size() - 1].map_index.size() > 1)
                {
                    std::cerr << "\e[0;31m" << "error write in server after a location" << "\e[0m" << std::endl;
                    this->error = 1;
                    return;
                }
                this->serv[this->serv.size() - 1].set_index(line, loc);
                continue;
            }
            if (line.compare(0, 8, "cgi_ext ") == 0 && in_s == 1 && in_l == 0)
            {
                if (this->serv[this->serv.size() - 1].set_cgi_ext(line) == 1)
                {
                    this->error = 1;
                    return;
                }
                continue;
            }
            if (line.compare(0, 8, "cgi_dir ") == 0 && in_s == 1 && in_l == 0)
            {
                if (this->serv[this->serv.size() - 1].set_cgi_dir(line) == 1)
                {
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 8, "rewrite ") == 0 && in_s == 1)
            {
                if (this->serv[this->serv.size() - 1].set_redirect(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "rediection not well configured exemple : rewrite index.html index.nginx-debian.html" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                continue;
            }
            if (line.compare(0, 13, "upload_store ") == 0 && in_s == 1)
            {
                if ((this->serv[this->serv.size() - 1].set_path_upload_dir(line)) == 1)
                {
                    this->error = 1;
                    return ;
                }
                continue;
            }
            std::cerr << "\e[0;31m" << "error ligne:" << line << " :not well configured:" <<"\e[0m" << std::endl;
            this->error = 1;
            return ;
        }
    }
    if (this->serv.size() == 0)
    {
        _ERR_FILE;
        this->error = 1;
        return;
    }

    for (size_t nb = 0; nb < this->serv.size(); nb++)
    {
        if (this->serv[nb].map_root[""] == "")
        {
            this->error = 1;
            std::cerr << "\e[0;31m" << "root empty the file .conf have to receive a root as argument" << "\e[0m" << std::endl;
            std::cerr << "\e[0;31m" << "exemple:root files_test;" << std::endl;
            return ;
        }
        if (this->serv[nb].tab_addr_port.size() == 0)
        {
            this->error = 1;
            std::cerr << "\e[0;31m" << "server have to listen on an address with a port" << "\e[0m" << std::endl;
            return ;
        }
        for (_MAP_L_EXEPT::iterator it = this->serv[nb].map_limit_exept.begin() ; it != this->serv[nb].map_limit_exept.end(); it++)
        {
            if (it->second.size() == 0)
            {
                it->second.push_back("GET");
                it->second.push_back("DELETE");
                it->second.push_back("POST");
            }
        }
        for (_MAP_INDEX::iterator it = this->serv[nb].map_index.begin(); it != this->serv[nb].map_index.end(); it++)
        {
            for (std::vector<std::string>::iterator ot = it->second.begin(); ot != it->second.end();)
            {
                std::ifstream file(this->serv[nb].get_root(it->first).append("/").append(*ot).c_str());
                if (!file)
                {
                    this->serv[nb].map_index[it->first].erase(ot);
                    ot = it->second.begin();
                }
                else
                {
                    file.close();
                    ot++;
                }
            }
            if (it->second.size() == 0)
                it->second.push_back("");
        }
        ////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////  REVOIR CETTE PARTIE PLUS TARD ////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////
        /*for (_MAP_ADDR_PORT::iterator it = this->serv[nb].tab_addr_port.begin(); it != this->serv[nb].tab_addr_port.end(); it++)
        {

        }*/
        // elem pour debug a enlever par la suite.
        //std::cout << this->serv[nb].get_root("/image/") << std::endl;
        //std::cout << this->serv[nb].get_error_page("/image/", 400) << std::endl;
        //std::cout << this->serv[nb].get_autoindex("/image/") << std::endl;
        //std::cout << this->serv[nb].get_client_max_body("/") << std::endl;
        /*std::vector<std::string> ko = this->serv[nb].get_all_index("/");
        for (std::vector<std::string>::iterator it = ko.begin(); it != ko.end(); it++)
            std::cout << *it << std::endl;*/
        /*std::vector<std::string> ko = this->serv[nb].get_addresses(18000);
        for (std::vector<std::string>::iterator it = ko.begin(); it != ko.end(); it++)
            std::cout << *it << std::endl;*/
        //////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////
        // for (_MAP_L_EXEPT::iterator it = this->serv[nb].map_limit_exept.begin(); it != this->serv[nb].map_limit_exept.end(); it++)
        // {
        //     std::cout << "loc :" << it->first; 
        //     for (std::vector<std::string>::iterator ot = it->second.begin(); ot != it->second.end(); ot++)
        //     {
        //         std::cout << " " << *ot;
        //     }
        //     std::cout << std::endl;
        // }
        // for (_MAP_REDIRECT::iterator it = this->serv[nb].map_redirect.begin(); it != this->serv[nb].map_redirect.end(); it++)
        // {
        //     std::cout << "loc :" << it->first; 
        //     for (std::map<std::string, std::string>::iterator ot = it->second.begin(); ot != it->second.end(); ot++)
        //     {
        //         std::cout << "first :" << ot->first << " " <<"second :" << ot->second;
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << ":\"\":" << this->serv[nb].get_redirect("", "index.html") << ":" << std::endl;
        // std::cout << ":/:" << this->serv[nb].get_redirect("/", "index.html") << ":" << std::endl;
        // std::cout << ":/batman/:" << this->serv[nb].get_redirect("/batman/", "index.html") << ":" << std::endl;
        // std::cout << "autoindex:" << this->serv[nb].get_autoindex("/") << std::endl;
        // std::cout << "s_name:" << this->serv[nb].s_name << std::endl;
        // std::cout << "extention";
        // for (_VEC_CGI_EXT::iterator it = this->serv[nb].tab_cgi_ext.begin(); it != this->serv[nb].tab_cgi_ext.end(); it++)
        //     std::cout << " " << *it;
        // std::cout << std::endl;
        // std::cout << "l'extention .php est elle autorise? " << this->serv[nb].ext_cgi_a(".py") << std::endl;
    }   
   /* this->tab_ap = get_all_addr_port();
    std::cout << this->tab_ap.size() << std::endl;*/

}

Parser::~Parser(){}


bool    Parser::check_error_bracket(bool s, bool l, bool elem) const
{
    if (elem == 0)
    {
        if (s == 1 || l == 1)
        {
            _ERR_FILE;
            return (1);
        }
    }
    else
    {
        if (l == 1 || s == 0)
        {
            _ERR_FILE;
            return (1);
        }
    }
    return (0);
}

bool    Parser::check_error_bracket_end(bool &s, bool &l)
{
    if (l == 1)
    {
        l = 0;
        return 0;
    }
    if (s == 1)
    {
        s = 0;
        return 0;
    }
    _ERR_FILE;
    return 1;
}

bool    Parser::set_error_page(std::string &line)
{
    line = line.substr(11);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    if (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        if (buff.size() > 3) {return (1);}
        for (std::string::iterator it = buff.begin(); it != buff.end(); it++)
        {
            if (!(std::isdigit(*it)))
                return (1);
        }
        int err = atoi(buff.c_str());
        if (err < 200 || (err > 200 && err < 301) || (err > 301 && err < 400) || (err > 418 && err < 421) || err == 430 || (err > 431 && err < 451) || (err > 451 && err < 500) || (err > 511))
        {
            std::cerr << err << " has not a good value to set an error" << std::endl;
            return (1);
        }
        std::string buff2 = line.substr(found + 1);
        std::ifstream file(buff2.c_str());
        if (!file)
        {
            std::cerr << "\e[0;31m" << "Error open file. The file doesn't exist." << "\e[0m" << std::endl;
            return (1);
        }
        file.close();
        this->error_p[err] = buff2;
        return (0);
    }
    return (1);
}

std::string Parser::new_location(std::string &line)
{
    line = line.substr(9);
    line = line.substr(0, line.length() -1);
    std::size_t found = line.find(" ");
    if (found!=std::string::npos)
        line = line.substr(0, found);
    return line;
}

bool    Parser::set_client_max_body(std::string &line)
{
    size_t size;
    line = line.substr(21);
    line = line.substr(0, line.length() - 1);
    for (std::string::iterator it = line.begin(); it != line.end(); it++)
    {
        if (!(std::isdigit(*it)))
            return (1);
    }
    if (line.length() > 13) {return (1);}
    std::stringstream sstream(line);
    sstream >> size;
    if (size > 8796093022207 || 0 > size) {return (1);}
    this->size_cmb = size;
    return (0);
}

void    Parser::set_root(std::string &line)
{
    line = line.substr(5);
    line = line.substr(0, line.length() - 1);
    if (line.size() > 0 && line[line.size() - 1] == '/')
        line = line.substr(0, line.length() - 1);
    this->root = line;
}

bool    Parser::set_autoindex(std::string &line)
{
    line = line.substr(10);
    line = line.substr(0, line.length() - 1);
    if (!(line == "on" || line == "off"))
        return (1);
    this->autoindex = (line == "on") ? 1 : 0;
    return (0);
}

void    Parser::set_index(std::string &line)
{
    _INDEX  index;
    line = line.substr(6);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    while (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        if (buff.size() != 0)
            index.push_back(buff);
        line = line.substr(found + 1);
        found = line.find(" ");
    }
    index.push_back(line);
    if (index.size() == 0)
        index.push_back("");
    this->index = index;
}

bool    Parser::check_if_error_parsing(std::vector<P_server> &servs)
{
    /*std::cout << "check error" << std::endl;
    for (size_t i = 0; i < servs.size(); i++)
    {
        for (_MAP_ADDR_PORT::iterator it = servs[i].tab_addr_port.begin(); it != servs[i].tab_addr_port.end(); it++)
            std::cout << "addresse " <<  it->first << " " << "port " << it->second << std::endl;
    }*/
    (void)servs;
    return (0);
}

std::set<std::pair<std::string, int> > Parser::get_all_addr_port(void)
{
    std::set<std::pair<std::string, int> >   lala;
    std::vector<P_server>   n_serv;

    this->tab_tab_ap.clear();
    for (size_t nb = 0; nb < this->serv.size(); nb++)
    {
        for (_MAP_ADDR_PORT::iterator it = this->serv[nb].tab_addr_port.begin(); it != this->serv[nb].tab_addr_port.end(); it++)
        {
            for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {
                std::pair<std::string, int> lala2 (*it2, it->first);
                std::pair<std::set<std::pair<std::string, int> >::iterator, bool > ret;
                ret = lala.insert(lala2);
                if (ret.second == 1)
                {   
                    std::pair<std::pair<std::string, int>, std::vector<P_server> > lalab2 (lala2, n_serv);
                    this->tab_tab_ap.insert(lalab2);
                    this->tab_tab_ap[lala2].push_back(this->serv[nb]);
                }
                else
                {
                    std::map<std::pair<std::string, int>, std::vector<P_server> >::iterator ot = this->tab_tab_ap.find(lala2);
                    if (ot != this->tab_tab_ap.end())
                        ot->second.push_back(this->serv[nb]);
                }
            }
        }
    }
    return (lala);
}

        //    std::ifstream file(buff.c_str());
        //     if (file)
        //     {
        //         index.push_back(buff);
        //         file.close();
        //     }