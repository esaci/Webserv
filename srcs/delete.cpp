// #include "include/ClassParsingClientRequest.hpp"
#include "../include/w_library.hpp"

//elias run ce test
// curl -X DELETE http://localhost:18000/prout -H "Accept: application/json"

int server_data::delete_request(int clientfd){
	int filefd;
	std::string root;

	// std::cout << "\n\nthis is delete test\n";
	// if ()
	tab_request[clientfd].ressource = tab_request[clientfd].u_ressource;
	root = serv_host(tab_tab_ap[sockets_to_hosts[tab_request[clientfd].serverfd]], tab_request[clientfd].host).get_root((char*)tab_request[clientfd].u_ressource.begin().base());
	tab_request[clientfd].ressource = _link_root_init(root, tab_request[clientfd].ressource);
	tab_request[clientfd].ressource.push_back('\0');
	std::cout << "ON SUPPRIME " << tab_request[clientfd].ressource << std::endl;
	filefd = open((char*)tab_request[clientfd].ressource.begin().base(), O_RDONLY);

	tab_request[clientfd].ressource.pop_back();
	if (filefd < 0)
	{
		tab_request[clientfd].return_error = 403;
		_get_error_403(clientfd);
		// tab_request[clientfd].return_error = 404;
		// _get_error_404(clientfd);
	}
	else if (1)
	{
		std::remove((char *)tab_request[clientfd].ressource.begin().base());
		tab_request[clientfd].r_buffer.clear();
		tab_request[clientfd].responding = 3;
		return (_send(clientfd, 200));
	}
	// if (1)
	// {
	// 	tab_request[clientfd].return_error = 403;
	// 	_get_error_403(clientfd);
	// }
    // char *pathtodelete = "./todelete"
    // //if exists
    // std::remove(path)

    // else
    //     404
	
	if (1)
	{
		tab_request[clientfd].return_error = 404;
		_get_error_404(clientfd);
	}
	
    //verifier que le psth existe
    //si le path est moins que / return 403
    //try to resolve url
    //si oui
        //std remove le path si ca mache renvoie 200 // ou 204 si on gere l'autorisation
        //sinon
            //revoie 403 forbiden // av oir avec l'autorisation
    // si le path existe pas
        //on retourne 404
    // if (this->responding < 2)
	// {
		// if (_set_file(clientfd))
			// return (_get_error_404(clientfd));
		// return (0);
	// }
	// return (_send(clientfd, 200));
	(void)filefd;
	return 0;

}