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
    this->tab_cgi_ext = copie.tab_cgi_ext;
    this->cgi_dir = copie.cgi_dir;
    this->map_redirect = copie.map_redirect;
    this->tab_ap = copie.tab_ap;
    this->path_upload_dir = copie.path_upload_dir;
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
        std::string fin = buff;
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
        this->tab_addr_port[port].push_back(fin);
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
    if (line.size() > 0 && line[line.size() - 1] == '/')
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
    this->map_autoindex[loc] = (line == "on") ? 1 : 0;
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

bool    P_server::set_cgi_ext(std::string &line)
{
    // quel cgi_extention accepter et renvoyer une une erreur si se n'est pas la bonne.
    std::vector<std::string>    lala;
    line = line.substr(8);
    line = line.substr(0, line.length() - 1);
    std::size_t found = line.find(" ");
    while (found!=std::string::npos)
    {
        std::string buff = line.substr(0, found);
        if (buff != ".py" && buff != ".php")
        {
            std::cerr << "\e[0;31m" << "cgi not well configured only .php and .py accept" << "\e[0m" << std::endl;
            return (1);
        }
        lala.push_back(buff);
        line = line.substr(found + 1);
        found = line.find(" ");
    }
    if (line != ".py" && line != ".php")
    {
        std::cerr << "\e[0;31m" << "cgi not well configured only .php and .py accept" << "\e[0m" << std::endl;
        return (1);
    }
    lala.push_back(line);
    this->tab_cgi_ext = lala;
    return (0);
}

void    P_server::set_cgi_dir(std::string &line)
{
    line = line.substr(8);
    line = line.substr(0, line.length() - 1);
    this->cgi_dir = line;
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

bool    P_server::set_path_upload_dir(std::string &line)
{
    line = line.substr(13);
    line = line.substr(0, line.length() - 1);
    if (line.size() > 0 && *(--line.end()) != '/')
        line.append("/");
    this->path_upload_dir = line;
    return (0);
}

std::string P_server::get_root(std::string loc)
{
    _MAP_ROOT::iterator it;
    std::string::iterator b;

    for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
        ;
    loc.erase(++b, loc.end());
    //std::cout << "LOC VAUT : |" << loc << "|" << std::endl; 
    it = this->map_root.find(loc);
    if (it == this->map_root.end())
    {
        it = this->map_root.find("/");
        if (it == this->map_root.end())
        {
            it = this->map_root.find("");
            return (it->second);
        }
        //return ("no find elem");// soit renvoyer une erreur;
        return (it->second);    // soit renvoyer le chemin par defaut;
    }
    return (it->second);
}

std::string P_server::get_error_page(std::string loc, int err)
{
    _MAP_ERRORP::iterator it;
    ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
    std::string::iterator b;
    for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
        ;
    loc.erase(++b, loc.end());
    ///////////////////////////////////////////////////////////////////////
    it = this->map_error_p.find(loc);
    if (it == this->map_error_p.end())
    {
        it = this->map_error_p.find("/");
        if (it == this->map_error_p.end())
        {
            it = this->map_error_p.find("");
            return (it->second[err]);
        }
        return (it->second[err]);
    }
    return (it->second[err]);
}

bool    P_server::get_autoindex(std::string loc)
{
    _MAP_AUTO_I::iterator it;
    ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
    std::string::iterator b;
    for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
        ;
    loc.erase(++b, loc.end());
    ///////////////////////////////////////////////////////////////////////
    it = this->map_autoindex.find(loc);
    if (it == this->map_autoindex.end())
    {
        it = this->map_autoindex.find("/");
        if (it == this->map_autoindex.end())
        {
            it = this->map_autoindex.find("");
            return (it->second);
        }
        return (it->second);
    }
    return (it->second);
}

size_t  P_server::get_client_max_body(std::string loc)
{
    _CMBS::iterator it;
    ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
    std::string::iterator b;
    for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
        ;
    loc.erase(++b, loc.end());
    ///////////////////////////////////////////////////////////////////////
    it = this->map_size_cmb.find(loc);
    if (it == this->map_size_cmb.end())
    {
        it = this->map_size_cmb.find("/");
        if (it == this->map_size_cmb.end())
        {
            it = this->map_size_cmb.find("");
            return (it->second);
        }
        return (it->second);
    }
    return (it->second);
}

std::vector<std::string>    P_server::get_all_index(std::string loc)
{
    _MAP_INDEX::iterator it;
    ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
    std::string::iterator b;
    for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
        ;
    loc.erase(++b, loc.end());
    ///////////////////////////////////////////////////////////////////////
    it = this->map_index.find(loc);
    if (it == this->map_index.end())
    {
        it = this->map_index.find("/");
        if (it == this->map_index.end())
        {
            it = this->map_index.find("");
            return (it->second);
        }
        return (it->second);
    }
    return (it->second);
}

std::vector<std::string>    P_server::get_addresses(int port)
{
    _MAP_ADDR_PORT::iterator it;
    it = this->tab_addr_port.find(port);
    if (it == this->tab_addr_port.end())
    {
        //je ne sais pas (voir apres quoi renvoyer)
        std::vector<std::string> lala;
        return (lala);
        //////////////////////////////////////////
    }
    return (it->second);
}

std::vector<std::string>    P_server::get_limit_exept(std::string loc)
{
    _MAP_L_EXEPT::iterator it;
    ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
    std::string::iterator b;
    for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
        ;
    loc.erase(++b, loc.end());
    ///////////////////////////////////////////////////////////////////////
    it = this->map_limit_exept.find(loc);
    if (it == this->map_limit_exept.end())
    {
        it = this->map_limit_exept.find("/");
        if (it == this->map_limit_exept.end())
        {
            it = this->map_limit_exept.find("");
            return (it->second);
        }
        return (it->second);
    }
    return (it->second);
}

std::string                 P_server::get_redirect(std::string loc, std::string page)
{
    _MAP_REDIRECT::iterator                         it;
    std::map<std::string, std::string>::iterator    ot;
    ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
    std::string::iterator b;
    for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
        ;
    loc.erase(++b, loc.end());
    ///////////////////////////////////////////////////////////////////////
    it = this->map_redirect.find(loc);
    if (it == this->map_redirect.end())
    {
        it = this->map_redirect.find("/");
        if (it == this->map_redirect.end())
        {
            it = this->map_redirect.find("");
            if (it == this->map_redirect.end())
                return (page);
            ot = it->second.find(page);
            if (ot == it->second.end())
                return (page);
            return (ot->second);
        }
        ot = it->second.find(page);
        if (ot == it->second.end())
            return (page);
        return (ot->second);
    }
    ot = it->second.find(page);
    if (ot == it->second.end())
        return (page);
    return (ot->second);
}


// std::vector<std::string>    P_server::get_cgi_ext(std::string loc)
// {
//     (void)loc;
//     std::vector<std::string> lala;
//     return (lala);
//     // _MAP_CGI_EXT::iterator it;
//     // ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
//     // std::string::iterator b;
//     // for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
//     //     ;
//     // loc.erase(++b, loc.end());
//     // ///////////////////////////////////////////////////////////////////////
//     // it = this->map_cgi_ext.find(loc);
//     // if (it == this->map_cgi_ext.end())
//     // {
//     //     it = this->map_cgi_ext.find("/");
//     //     return (it->second);
//     // }
//     // return (it->second);
// }



// std::string P_server::get_cgi_dir(std::string loc)
// {
//     _MAP_CGI_DIR::iterator it;
//     ////////////////////////////////////// dans tous les getters, mettre loc dans un nouveau string et retirer tout apres le dernier ‘\’
//     std::string::iterator b;
//     for (b = --loc.end(); b >= loc.begin() && *b != '/'; b--)
//         ;
//     loc.erase(++b, loc.end());
//     ///////////////////////////////////////////////////////////////////////
//     it = this->map_cgi_dir.find(loc);
//     if (it == this->map_cgi_dir.end())
//     {
//         it = this->map_cgi_dir.find("/");
//         return (it->second);
//     }
//     return (it->second);
// }


bool    P_server::ext_cgi_a(std::string ext)
{
    for (_VEC_CGI_EXT::iterator it = this->tab_cgi_ext.begin(); it != this->tab_cgi_ext.end(); it++)
        if (*it == ext) return (1);
    return (0);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////function en dehors de P_server mais lier //
/////////////////////////////////////////////////////////////////////////////////////

std::string get_root(std::vector<P_server> tab, std::string name, std::pair<std::string, int> ap, std::string loc)
{
    for (std::vector<P_server>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        if (it->s_name == name)
        {
            for (_MAP_ADDR_PORT::iterator it2 = it->tab_addr_port.begin(); it2 != it->tab_addr_port.end(); it2++)
            {
                if (it2->first == ap.second)
                {
                    for (std::vector<std::string>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                    {
                        if (*it3 == ap.first)
                            return (it->get_root(loc));
                    }
                }
            }
        }
    }
    std::vector<P_server>::iterator it = tab.begin();
    return it->get_root(loc);
}