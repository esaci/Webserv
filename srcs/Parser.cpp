#include "../include/Parser.hpp"

Parser::Parser(std::fstream &file)
{
    this->error = 0;
    std::string line;
    bool    in_s = 0;   // pour savoir si je suis dans une directive de block server
    bool    in_l = 0;   // pour savoir si je suis dans une directive de block location
    std::string loc = ""; // me sert a la location par deafaut;

    while (std::getline(file, line))
    {
        int     i = 0; // sert a enlever les premiers ' ' de chaque ligne
        for (; line[i] == ' ' || line[i] == 9; i++){}
        line = line.substr(i);
        if (line.length() != 0 && line[0] != '#')
        {
            if (!((*(line.end() - 1) == ';' || *(line.end() - 1) == '{' || *(line.end() - 1) == '}')))
            {
                _ERR_FILE;
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
            }
            if (line.compare(0, 9,"location ") == 0 && (*(line.end() - 1)) == '{')
            {
                if (check_error_bracket(in_s, in_l, 1) == 1) return ;
                in_l = 1;
                loc = this->new_location(line);
                // faire une verif si le loc est ok
                this->serv[this->serv.size() - 1].map_error_p[loc] = this->serv[this->serv.size() - 1].map_error_p[""];
                this->serv[this->serv.size() - 1].map_size_cmb[loc] = this->serv[this->serv.size() - 1].map_size_cmb[""];
                this->serv[this->serv.size() - 1].map_root[loc] = this->serv[this->serv.size() - 1].map_root[""];
                this->serv[this->serv.size() - 1].map_limit_exept[loc] = this->serv[this->serv.size() - 1].map_limit_exept[""];
                this->serv[this->serv.size() - 1].map_autoindex[loc] = this->serv[this->serv.size() - 1].map_autoindex[""];
                this->serv[this->serv.size() - 1].map_index[loc] = this->serv[this->serv.size() - 1].map_index[""];
            }
            if (line == "}" && check_error_bracket_end(in_s, in_l) == 1)
                return ;
            if (line.compare(0,7, "listen ") == 0 && in_s == 1 && in_l == 0)
            {
                if (this->serv[this->serv.size() - 1].set_new_port(line) == 1)
                {
                    std::cerr << "\e[0;31m" << "listen is not well configured exemple: listen 127.0.0.1:80;" << "\e[0m"<< std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 12, "server_name") == 0 && in_s == 1 && in_l == 0)
                this->serv[this->serv.size() - 1].set_s_name(line);
            if (line.compare(0, 11, "error_page ") == 0 && in_s == 0)
            {
                if (this->serv.size() > 0)
                {
                    std::cerr << "\e[0;31m" << "you have to put value before location" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
                if (this->set_error_page(line) == 1)
                {
                     std::cerr << "\e[0;31m" << "error page not well configured exemple: error_page 404 www/error_page_404.html;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 11, "error_page ") == 0 && in_s == 1)
            {
                if (this->serv[this->serv.size() - 1].set_error_page(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "error page not well configured exemple: error_page 404 www/error_page_404.html;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 21, "client_max_body_size ") == 0 && in_s == 0)
            {
                if (this->set_client_max_body(line) == 1)
                {
                    std::cerr << "\e[0;31m" << "client_max_body_size not well configured exemple: client_max_body_size 100;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 21, "client_max_body_size ") == 0 && in_s == 1)
            {
                if (this->serv[this->serv.size() - 1].set_client_max_body(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "client_max_body_size not well configured exemple: client_max_body_size 100;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 5, "root ") == 0 && in_s == 0)
                this->set_root(line);
            if (line.compare(0, 5, "root ") == 0 && in_s == 1 && in_l == 0)
                this->serv[this->serv.size() - 1].set_root(line, loc);
            if (line.compare(0, 13, "limit_except ") == 0 && in_s == 1 && in_l == 1)
            {
                if (this->serv[this->serv.size() - 1].set_limit_exept(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "limit_except not well configured limit_except GET POST DELETE;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 10, "autoindex ") == 0 && in_s == 0)
            {
                if (this->set_autoindex(line) == 1)
                {
                    std::cerr << "\e[0;31m" << "autoindex not well configured exemple: autoindex off;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 10, "autoindex ") == 0 && in_s == 1)
            {
                if (this->serv[this->serv.size() - 1].set_autoindex(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "autoindex not well configured exemple: autoindex off;" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
            if (line.compare(0, 6, "index ") == 0 && in_s == 0)
                this->set_index(line);
            if (line.compare(0, 6, "index ") == 0 && in_s == 1)
                this->serv[this->serv.size() - 1].set_index(line, loc);
            if (line.compare(0, 8, "cgi_ext ") == 0 && in_s == 1 && in_l == 1)
                this->serv[this->serv.size() - 1].set_cgi_ext(line, loc);
            if (line.compare(0, 8, "cgi_dir ") == 0 && in_s == 1 && in_l == 1)
                this->serv[this->serv.size() - 1].set_cgi_dir(line, loc);
            if (line.compare(0, 8, "rewrite ") == 0 && in_s == 1)
            {
                if (this->serv[this->serv.size() - 1].set_redirect(line, loc) == 1)
                {
                    std::cerr << "\e[0;31m" << "rediection not well configured exemple : rewrite index.html index.nginx-debian.html" << "\e[0m" << std::endl;
                    this->error = 1;
                    return ;
                }
            }
        }
    }
    if (this->serv.size() == 0)
    {
        _ERR_FILE;
        this->error = 1;
        return;
    }

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
        //int last = line.find_last_of (" ");
        //std::string buff2 = line.substr(last + 1, line.size() - last);
        std::string buff2 = line.substr(found + 1);
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
    if (size > 8796093022207) {return (1);}
    this->size_cmb = size;
    return (0);
}

void    Parser::set_root(std::string &line)
{
    line = line.substr(5);
    line = line.substr(0, line.length() - 1);
    this->root = line;
}

bool    Parser::set_autoindex(std::string &line)
{
    line = line.substr(10);
    line = line.substr(0, line.length() - 1);
    if (!(line == "on" || line == "off"))
        return (1);
    this->autoindex = line;
    return (0);
}

void    Parser::set_index(std::string &line)
{
    line = line.substr(6);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    while (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        this->index.push_back(buff);
        line = line.substr(found + 1);
        found = line.find(" ");
    }
    this->index.push_back(line);
}

bool    Parser::check_if_error_parsing(std::vector<P_server> &servs)
{
    std::cout << "check error" << std::endl;
    for (size_t i = 0; i < servs.size(); i++)
    {
        for (_MAP_ADDR_PORT::iterator it = servs[i].tab_addr_port.begin(); it != servs[i].tab_addr_port.end(); it++)
            std::cout << "addresse " <<  it->first << " " << "port " << it->second << std::endl;
    }
    return (0);
}