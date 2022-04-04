#include "../include/Parser.hpp"

P_server::P_server():tab_addr_port(){}
P_server::P_server(const P_server &arg):tab_addr_port(){
    *this = arg;
}
P_server::~P_server(){}

P_server &  P_server::operator=(const P_server &copie) 
{
    this->tab_addr_port = copie.tab_addr_port;
    this->s_name = copie.s_name;
    this->map_error_p = copie.map_error_p;
    this->map_size_cmb = copie.map_size_cmb;
    this->map_root = copie.map_root;
    this->map_limit_exept = copie.map_limit_exept;
    this->map_autoindex = copie.map_autoindex;
    this->map_index = copie.map_index;
    this->map_cgi_ext = copie.map_cgi_ext;
    this->map_cgi_dir = copie.map_cgi_dir;
    this->map_redirect = copie.map_redirect;
    return (*this);
}

bool    P_server::set_new_port(std::string &line)
{
    line = line.substr(7);
    line = line.substr(0, line.length() - 1);
    std::string buff = line;
    std::size_t found = buff.find(":");
    if (found!=std::string::npos)
    {
        buff = line.substr(0, found);
        std::string buff2 = line.substr(found + 1, line.size());
        found = buff.find(".");
        int size = 0;
        while (found != std::string::npos)
        {
            std::string buff3 = buff.substr(0, found);
            for (std::string::iterator it = buff3.begin(); it != buff3.end(); it++)
            {
                if (!(std::isdigit(*it)))
                    return (1);
            }
            int num = atoi(buff3.c_str());
            if (num < 0 || num > 255)
                return (1);
            buff = buff.substr(found + 1, buff.size());
            found = buff.find(".");
            size++;
        }
        if (size != 3)
            return (1);
        std::string buff3 = buff.substr(0, found);
        for (std::string::iterator it = buff3.begin(); it != buff3.end(); it++)
        {
            if (!(std::isdigit(*it)))
                return (1);
        }
        int num = atoi(buff3.c_str());
        if (num < 0 || num > 255)
            return (1);

        for (int i = 0; buff2[i] != '\0'; i++)
            if (!(std::isdigit(buff2[i])))
                return (1);
        if (buff2.size() > 10)
            return (1);
        int port = atoi(buff2.c_str());
        this->tab_addr_port[buff] = port;
        return (0);
    }
    return (1);
}

void    P_server::set_s_name(std::string &line)
{
    line = line.substr(12);
    line = line.substr(0, line.length() - 1);
    this->s_name = line;
}

bool    P_server::set_error_page(std::string &line, std::string &loc)
{
    line = line.substr(11);
    line = line.substr(0, line.length() -1);
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
        std::string buff2 = line.substr(found + 1);
        this->map_error_p[loc][err] = buff2;
        return (0);
    }
    return (1);
}

bool    P_server::set_client_max_body(std::string &line, std::string &loc)
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
    this->map_size_cmb[loc] = size;
    return (0);
}

void    P_server::set_root(std::string &line, std::string &loc)
{
    line = line.substr(5);
    line = line.substr(0, line.length() - 1);
    this->map_root[loc] = line;
}

bool    P_server::set_limit_exept(std::string &line, std::string &loc)
{
    std::vector<std::string> lala;
    int size = 0;
    line = line.substr(13);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    while (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        if (!(buff == "GET" || buff == "DELETE" || buff == "POST"))
            return (1);
        lala.push_back(buff);
        line = line.substr(found + 1);
        found = line.find(" ");
        size++;
    }
    if (size == 0) {return (1);}
    lala.push_back(line);
    this->map_limit_exept[loc] = lala;
    return (0);
}

bool    P_server::set_autoindex(std::string &line, std::string &loc)
{
    line = line.substr(10);
    line = line.substr(0, line.length() - 1);
    if (!(line == "on" || line == "off"))
        return (1);
    this->map_autoindex[loc] = line;
    return (0);
}

void    P_server::set_index(std::string &line, std::string &loc)
{
    _INDEX  lala;
    line = line.substr(6);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    while (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        lala.push_back(buff);
        line = line.substr(found + 1);
        found = line.find(" ");
    }
    lala.push_back(line);
    this->map_index[loc] = lala;
}

void    P_server::set_cgi_ext(std::string &line, std::string &loc)
{
    // quel cgi_extention accepter et renvoyer une une erreur si se n'est pas la bonne.
    std::vector<std::string>    lala;
    line = line.substr(8);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    while (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        lala.push_back(buff);
        line = line.substr(found + 1);
        found = line.find(" ");
    }
        lala.push_back(line);
        this->map_cgi_ext[loc] = lala;
}

void    P_server::set_cgi_dir(std::string &line, std::string &loc)
{
    line = line.substr(8);
    line = line.substr(0, line.length() - 1);
    this->map_cgi_dir[loc] = line;
}

bool    P_server::set_redirect(std::string &line, std::string &loc)
{
    line = line.substr(8);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    if (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        line = line.substr(found + 1);
        this->map_redirect[loc][buff] = line;
        return (0);
    }
    return (1);
}