#include "../include/w_library.hpp"

C_DATA *_code_init( void ){
	C_DATA *tmp;

	tmp = new C_DATA();

	tmp->insert(std::pair<int, std::string>(100, "Continue"));
	tmp->insert(std::pair<int, std::string>(101, "Switching Protocols"));
	tmp->insert(std::pair<int, std::string>(200, "OK"));
	tmp->insert(std::pair<int, std::string>(201, "Created"));
	tmp->insert(std::pair<int, std::string>(202, "Accepted"));
	tmp->insert(std::pair<int, std::string>(203, "Non-Authoritative Information"));
	tmp->insert(std::pair<int, std::string>(204, "No Content"));
	tmp->insert(std::pair<int, std::string>(205, "Reset Content"));
	tmp->insert(std::pair<int, std::string>(206, "Partial Content"));
	tmp->insert(std::pair<int, std::string>(300, "Multiple Choices"));
	tmp->insert(std::pair<int, std::string>(301, "Moved Permanently"));
	tmp->insert(std::pair<int, std::string>(302, "Found"));
	tmp->insert(std::pair<int, std::string>(303, "See Other"));
	tmp->insert(std::pair<int, std::string>(304, "Not Modified"));
	tmp->insert(std::pair<int, std::string>(305, "Use Proxy"));
	// tmp.insert(std::pair<int, std::string>(306, ("Unused)"));
	tmp->insert(std::pair<int, std::string>(307, "Temporary Redirect"));
	tmp->insert(std::pair<int, std::string>(400, "Bad Request"));
	tmp->insert(std::pair<int, std::string>(401, "Unauthorized"));
	tmp->insert(std::pair<int, std::string>(402, "Payment Required"));
	tmp->insert(std::pair<int, std::string>(403, "Forbidden"));
	tmp->insert(std::pair<int, std::string>(404, "Not Found"));
	tmp->insert(std::pair<int, std::string>(405, "Method Not Allowed"));
	tmp->insert(std::pair<int, std::string>(406, "Not Acceptable"));
	tmp->insert(std::pair<int, std::string>(407, "Proxy Authentication Required"));
	tmp->insert(std::pair<int, std::string>(408, "Request Timeout"));
	tmp->insert(std::pair<int, std::string>(10,  "409 Conflict"));
	tmp->insert(std::pair<int, std::string>(1410, "Gone"));
	tmp->insert(std::pair<int, std::string>(1411, "Length Required"));
	tmp->insert(std::pair<int, std::string>(1412, "Precondition Failed"));
	tmp->insert(std::pair<int, std::string>(1413, "Request Entity Too Large"));
	tmp->insert(std::pair<int, std::string>(1414, "Request-URI Too Long"));
	tmp->insert(std::pair<int, std::string>(1415, "Unsupported Media Type"));
	tmp->insert(std::pair<int, std::string>(1416, "Requested Range Not Satisfiable"));
	tmp->insert(std::pair<int, std::string>(18,   "417 Expectation Failed"));
	tmp->insert(std::pair<int, std::string>(500, "Internal Server Error"));
	tmp->insert(std::pair<int, std::string>(501, "Not Implemented"));
	tmp->insert(std::pair<int, std::string>(502, "Bad Gateway"));
	tmp->insert(std::pair<int, std::string>(503, "Service Unavailable"));
	tmp->insert(std::pair<int, std::string>(504, "Gateway Timeout"));
	tmp->insert(std::pair<int, std::string>(505, "HTTP Version Not Supported"));
	return (tmp);
}

std::string display_code(int code, std::string &value)
{
	std::string tmp;
	
	tmp += code;
	tmp += value;
	return (tmp);
}