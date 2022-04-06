// #include "include/ClassParsingClientRequest.hpp"
#include "../include/w_library.hpp"

//elias run ce test
// curl -X DELETE http://localhost:1818/prout -H "Accept: application/json"

int RP15::delete_request(server_data *d_s, int clientfd){
    (void)d_s;
    (void)clientfd;
    std::cout << "\n\nthis is delete test\n";
    // char *pathtodelete = "./todelete"

    // //if exists
    // std::remove(path)

    // else
    //     404


    //verifier que le psth existe
    //si le path est moins que / return 403
    //try to resolve url
    //si oui
        //std remove le path si ca mache renvoie 200 // ou 204 si on gere l'autorisation
        //sinon
            //revoie 403 forbiden // av oir avec l'autorisation
    // si le path existe pas
        //on retourne 404
    if (this->responding < 2)
	{
		if (d_s->_set_file(clientfd))
			return (d_s->_get_error_404(clientfd));
		return (0);
	}
	return (d_s->_send(clientfd, 200));
    return 0;

}