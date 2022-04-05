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
    return 0;

}