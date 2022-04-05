#include "../include/w_library.hpp"

server_data::server_data(std::fstream &file){
	(void)file;
	_code_init();
	_content_type();
	serverfd = -1;
	recvline.resize(MAXLINE + 10);
	listening = false;
}
server_data::~server_data( void ){
	if (serverfd >= 0 || serverfd == -2)
		close(serverfd);
}


void	server_data::_table_poll_init( void ){
	tab_poll.clear();
	if (serverfd < 0)
		return ;
	client_poll.fd = serverfd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	tab_poll.push_back(client_poll);
}

void	server_data::_code_init( void ){
	codes.insert(std::pair<int, std::string>(100, "Continue"));
	codes.insert(std::pair<int, std::string>(101, "Switching Protocols"));
	codes.insert(std::pair<int, std::string>(200, "OK"));
	codes.insert(std::pair<int, std::string>(201, "Created"));
	codes.insert(std::pair<int, std::string>(202, "Accepted"));
	codes.insert(std::pair<int, std::string>(203, "Non-Authoritative Information"));
	codes.insert(std::pair<int, std::string>(204, "No Content"));
	codes.insert(std::pair<int, std::string>(205, "Reset Content"));
	codes.insert(std::pair<int, std::string>(206, "Partial Content"));
	codes.insert(std::pair<int, std::string>(300, "Multiple Choices"));
	codes.insert(std::pair<int, std::string>(301, "Moved Permanently"));
	codes.insert(std::pair<int, std::string>(302, "Found"));
	codes.insert(std::pair<int, std::string>(303, "See Other"));
	codes.insert(std::pair<int, std::string>(304, "Not Modified"));
	codes.insert(std::pair<int, std::string>(305, "Use Proxy"));
	// codes.insert(std::pair<int, std::string>(306, ("Unused)"));
	codes.insert(std::pair<int, std::string>(307, "Temporary Redirect"));
	codes.insert(std::pair<int, std::string>(400, "Bad Request"));
	codes.insert(std::pair<int, std::string>(401, "Unauthorized"));
	codes.insert(std::pair<int, std::string>(402, "Payment Required"));
	codes.insert(std::pair<int, std::string>(403, "Forbidden"));
	codes.insert(std::pair<int, std::string>(404, "Not Found"));
	codes.insert(std::pair<int, std::string>(405, "Method Not Allowed"));
	codes.insert(std::pair<int, std::string>(406, "Not Acceptable"));
	codes.insert(std::pair<int, std::string>(407, "Proxy Authentication Required"));
	codes.insert(std::pair<int, std::string>(408, "Request Timeout"));
	codes.insert(std::pair<int, std::string>(10,  "409 Conflict"));
	codes.insert(std::pair<int, std::string>(1410, "Gone"));
	codes.insert(std::pair<int, std::string>(1411, "Length Required"));
	codes.insert(std::pair<int, std::string>(1412, "Precondition Failed"));
	codes.insert(std::pair<int, std::string>(1413, "Request Entity Too Large"));
	codes.insert(std::pair<int, std::string>(1414, "Request-URI Too Long"));
	codes.insert(std::pair<int, std::string>(1415, "Unsupported Media Type"));
	codes.insert(std::pair<int, std::string>(1416, "Requested Range Not Satisfiable"));
	codes.insert(std::pair<int, std::string>(18,   "417 Expectation Failed"));
	codes.insert(std::pair<int, std::string>(500, "Internal Server Error"));
	codes.insert(std::pair<int, std::string>(501, "Not Implemented"));
	codes.insert(std::pair<int, std::string>(502, "Bad Gateway"));
	codes.insert(std::pair<int, std::string>(503, "Service Unavailable"));
	codes.insert(std::pair<int, std::string>(504, "Gateway Timeout"));
	codes.insert(std::pair<int, std::string>(505, "HTTP Version Not Supported"));
}

std::string server_data::display_code(int n_code)
{	
	std::stringstream out;

	out << n_code;
	std::string tmp = out.str();
	tmp += " ";
	tmp += codes[n_code];
	return (tmp);
}

void	server_data::_content_type( void ){
	ctypes.insert(std::pair<std::string, std::string>(std::string("html"),std::string("text/html")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("htm"),std::string("text/html")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("shtml"),std::string("text/html")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("css"),std::string("text/css")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("xml"),std::string("text/xml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("gif"),std::string("image/gif")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("jpeg"),std::string("image/gif")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("jpg"),std::string("image/jpeg")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("js"),std::string("application/javascript")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("atom"),std::string("application/atom+xml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("rss"),std::string("application/rss+xml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mml"),std::string("text/mathml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("txt"),std::string("text/plain")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("jad"),std::string("text/vnd.sun.j2me.app-descriptor")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("wml"),std::string("text/vnd.wap.wml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("htc"),std::string("text/x-component")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("png"),std::string("image/png")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("tif"),std::string("image/png")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("tiff"),std::string("image/tiff")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("wbmp"),std::string("image/vnd.wap.wbmp")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ico"),std::string("image/x-icon")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("jng"),std::string("image/x-jng")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("bmp"),std::string("image/x-ms-bmp")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("svg"),std::string("image/x-ms-bmp")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("svgz"),std::string("image/svg+xml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("webp"),std::string("image/webp")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("woff"),std::string("application/font-woff")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("jar"),std::string("application/font-woff")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("war"),std::string("application/font-woff")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ear"),std::string("application/java-archive")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("json"),std::string("application/json")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("hqx"),std::string("application/mac-binhex40")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("doc"),std::string("application/msword")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("pdf"),std::string("application/pdf")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ps"),std::string("application/pdf")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("eps"),std::string("application/pdf")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ai"),std::string("application/postscript")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("rtf"),std::string("application/rtf")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("m3u8"),std::string("application/vnd.apple.mpegurl")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("xls"),std::string("application/vnd.ms-excel")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("eot"),std::string("application/vnd.ms-fontobject")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ppt"),std::string("application/vnd.ms-powerpoint")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("wmlc"),std::string("application/vnd.wap.wmlc")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("kml"),std::string("application/vnd.google-earth.kml+xml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("kmz"),std::string("application/vnd.google-earth.kmz")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("7z"),std::string("application/x-7z-compressed")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("cco"),std::string("application/x-cocoa")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("jardiff"),std::string("application/x-java-archive-diff")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("jnlp"),std::string("application/x-java-jnlp-file")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("run"),std::string("application/x-makeself")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("pl"),std::string("application/x-makeself")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("pm"),std::string("application/x-perl")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("prc"),std::string("application/x-perl")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("pdb"),std::string("application/x-pilot")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("rar"),std::string("application/x-rar-compressed")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("rpm"),std::string("application/x-redhat-package-manager")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("sea"),std::string("application/x-sea")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("swf"),std::string("application/x-shockwave-flash")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("sit"),std::string("application/x-stuffit")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("tcl"),std::string("application/x-stuffit")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("tk"),std::string("application/x-tcl")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("der"),std::string("application/x-tcl")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("pem"),std::string("application/x-tcl")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("crt"),std::string("application/x-x509-ca-cert")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("xpi"),std::string("application/x-xpinstall")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("xhtml"),std::string("application/xhtml+xml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("xspf"),std::string("application/xspf+xml")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("zip"),std::string("application/zip")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("bin"),std::string("application/zip")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("exe"),std::string("application/zip")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("dll"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("deb"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("dmg"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("iso"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("img"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("msi"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("msp"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("msm"),std::string("application/octet-stream")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("docx"),std::string("application/vnd.openxmlformats-officedocument.wordprocessingml.document")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("xlsx"),std::string("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("pptx"),std::string("application/vnd.openxmlformats-officedocument.presentationml.presentation")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mid"),std::string("application/vnd.openxmlformats-officedocument.presentationml.presentation")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("midi"),std::string("application/vnd.openxmlformats-officedocument.presentationml.presentation")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("kar"),std::string("audio/midi")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mp3"),std::string("audio/mpeg")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ogg"),std::string("audio/ogg")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("m4a"),std::string("audio/x-m4a")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ra"),std::string("audio/x-realaudio")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("3gpp"),std::string("audio/x-realaudio")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("3gp"),std::string("video/3gpp")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("ts"),std::string("video/mp2t")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mp4"),std::string("video/mp4")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mpeg"),std::string("video/mp4")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mpg"),std::string("video/mpeg")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mov"),std::string("video/quicktime")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("webm"),std::string("video/webm")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("flv"),std::string("video/x-flv")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("m4v"),std::string("video/x-m4v")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("mng"),std::string("video/x-mng")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("asx"),std::string("video/x-mng")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("asf"),std::string("video/x-ms-asf")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("wmv"),std::string("video/x-ms-wmv")));
	ctypes.insert(std::pair<std::string, std::string>(std::string("avi"),std::string("video/x-msvideo")));
}

