#ifndef W_DEFINES_HPP
# define W_DEFINES_HPP

#	define SERVER_PORT 18000
#	define MAXLINE 100
#	define NBRCLIENTMAX 100
#	define TIMEOUT 100000
#	define TIMEOUT_CLIENT	1
#	define ADR	"127.0.0.1"
#	define ROOT "./files_test"
#	define TMPINDEX "/index.html"
#	define TMPFAVICO "./files_test/favicon.ico"
#	define ERRORFILE_400 "./files_system/Bad_Request.html"
#	define ERRORFILE_301 "./files_system/Moved_Permanently.html"
#	define ERRORFILE_404 "./files_system/Not_Found.html"
#	define ERRORFILE_408 "./files_system/Request_Timeout.html"
#	define FILE_CGI	"./files_system/file_cgi.html"
#	define METHOD	"GET"
#	define TARGET	"/"
#	define AUTOINDEX	0
#	define SA		struct sockaddr
#	define SA_IN	struct sockaddr_in
#	define DATA		std::vector<unsigned char>
#	define C_DATA	std::map<int, std::string>
#	define CT_DATA	std::map<std::string, std::string>
#	define R_DATA	std::map<int, RP15>
#	define RP15 ClassParsingClientRequest
// sudo apt-get install -y php-cgi
#	define CGI "/usr/lib/cgi-bin/php" 
#endif
