#ifndef W_DEFINES_HPP
# define W_DEFINES_HPP

#	define MAXLINE 10000000
#	define NBRCLIENTMAX 100
#	define TIMEOUT 100000
#	define TIMEOUT_CLIENT	50000
#	define MAX_SIZE_ENTITY 10000
#	define MAX_SIZE_URL 2048
// #	define ROOT "./files_test"
// #	define TMPINDEX "/index.html"
// #	define TMPFAVICO "./files_test/favicon.ico"
// #	define ERRORFILE_400 "./files_system/Bad_Request.html"
// #	define ERRORFILE_301 "./files_system/Moved_Permanently.html"
// #	define ERRORFILE_404 "./files_system/Not_Found.html"
// #	define ERRORFILE_403 "./files_system/Forbidden.html"
// #	define ERRORFILE_408 "./files_system/Request_Timeout.html"
#	define FILE_CGI	"./files_system/file_cgi.html"

// #	define AUTOINDEX	1
#	define SA		struct sockaddr
#	define SA_IN	struct sockaddr_in
#	define DATA		std::vector<unsigned char>
#	define C_DATA	std::map<int, std::string>
#	define CT_DATA	std::map<std::string, std::string>
#	define R_DATA	std::map<int, RP15>
#	define RP15 ClassParsingClientRequest
#	define A_P	std::pair<std::string, int>
#	define S_A_P	std::map<int, A_P>
//	sudo apt-get install -y php-cgi
#	define CGI "/usr/bin/php-cgi" 

# define _ERRORP        std::map<int, std::string>
# define _MAP_ERRORP    std::map<std::string, _ERRORP>
# define _INDEX         std::vector<std::string>
# define _MAP_ADDR_PORT std::map<int, std::vector<std::string> >
# define _MAP_ROOT      std::map<std::string, std::string>
# define _MAP_L_EXEPT   std::map<std::string, std::vector<std::string> >
# define _MAP_AUTO_I    std::map<std::string, bool>
# define _CMBS          std::map<std::string, size_t> // client max size;
# define _MAP_INDEX     std::map<std::string, _INDEX>
# define _VEC_CGI_EXT   std::vector<std::string>
# define _MAP_CGI_DIR   std::map<std::string, std::string>
# define _MAP_REDIRECT  std::map<std::string, std::map<std::string, std::string> >
# define _ERR_FILE      std::cout << "\e[0;31m" << "error_file" << "\e[0m" << std::endl

// define Parsing 
#endif
