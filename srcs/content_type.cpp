#include "../include/w_library.hpp"

CT_DATA *_content_type( void ){
	CT_DATA *tmp = new CT_DATA();

	tmp->insert(std::pair<std::string, std::string>(std::string(""),std::string("")));
	tmp->insert(std::pair<std::string, std::string>(std::string("html"),std::string("text/html")));
	tmp->insert(std::pair<std::string, std::string>(std::string("htm"),std::string("text/html")));
	tmp->insert(std::pair<std::string, std::string>(std::string("shtml"),std::string("text/html")));
	tmp->insert(std::pair<std::string, std::string>(std::string("css"),std::string("text/css")));
	tmp->insert(std::pair<std::string, std::string>(std::string("xml"),std::string("text/xml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("gif"),std::string("image/gif")));
	tmp->insert(std::pair<std::string, std::string>(std::string("jpeg"),std::string("image/gif")));
	tmp->insert(std::pair<std::string, std::string>(std::string("jpg"),std::string("image/jpeg")));
	tmp->insert(std::pair<std::string, std::string>(std::string("js"),std::string("application/javascript")));
	tmp->insert(std::pair<std::string, std::string>(std::string("atom"),std::string("application/atom+xml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("rss"),std::string("application/rss+xml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mml"),std::string("text/mathml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("txt"),std::string("text/plain")));
	tmp->insert(std::pair<std::string, std::string>(std::string("jad"),std::string("text/vnd.sun.j2me.app-descriptor")));
	tmp->insert(std::pair<std::string, std::string>(std::string("wml"),std::string("text/vnd.wap.wml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("htc"),std::string("text/x-component")));
	tmp->insert(std::pair<std::string, std::string>(std::string("png"),std::string("image/png")));
	tmp->insert(std::pair<std::string, std::string>(std::string("tif"),std::string("image/png")));
	tmp->insert(std::pair<std::string, std::string>(std::string("tiff"),std::string("image/tiff")));
	tmp->insert(std::pair<std::string, std::string>(std::string("wbmp"),std::string("image/vnd.wap.wbmp")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ico"),std::string("image/x-icon")));
	tmp->insert(std::pair<std::string, std::string>(std::string("jng"),std::string("image/x-jng")));
	tmp->insert(std::pair<std::string, std::string>(std::string("bmp"),std::string("image/x-ms-bmp")));
	tmp->insert(std::pair<std::string, std::string>(std::string("svg"),std::string("image/x-ms-bmp")));
	tmp->insert(std::pair<std::string, std::string>(std::string("svgz"),std::string("image/svg+xml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("webp"),std::string("image/webp")));
	tmp->insert(std::pair<std::string, std::string>(std::string("woff"),std::string("application/font-woff")));
	tmp->insert(std::pair<std::string, std::string>(std::string("jar"),std::string("application/font-woff")));
	tmp->insert(std::pair<std::string, std::string>(std::string("war"),std::string("application/font-woff")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ear"),std::string("application/java-archive")));
	tmp->insert(std::pair<std::string, std::string>(std::string("json"),std::string("application/json")));
	tmp->insert(std::pair<std::string, std::string>(std::string("hqx"),std::string("application/mac-binhex40")));
	tmp->insert(std::pair<std::string, std::string>(std::string("doc"),std::string("application/msword")));
	tmp->insert(std::pair<std::string, std::string>(std::string("pdf"),std::string("application/pdf")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ps"),std::string("application/pdf")));
	tmp->insert(std::pair<std::string, std::string>(std::string("eps"),std::string("application/pdf")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ai"),std::string("application/postscript")));
	tmp->insert(std::pair<std::string, std::string>(std::string("rtf"),std::string("application/rtf")));
	tmp->insert(std::pair<std::string, std::string>(std::string("m3u8"),std::string("application/vnd.apple.mpegurl")));
	tmp->insert(std::pair<std::string, std::string>(std::string("xls"),std::string("application/vnd.ms-excel")));
	tmp->insert(std::pair<std::string, std::string>(std::string("eot"),std::string("application/vnd.ms-fontobject")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ppt"),std::string("application/vnd.ms-powerpoint")));
	tmp->insert(std::pair<std::string, std::string>(std::string("wmlc"),std::string("application/vnd.wap.wmlc")));
	tmp->insert(std::pair<std::string, std::string>(std::string("kml"),std::string("application/vnd.google-earth.kml+xml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("kmz"),std::string("application/vnd.google-earth.kmz")));
	tmp->insert(std::pair<std::string, std::string>(std::string("7z"),std::string("application/x-7z-compressed")));
	tmp->insert(std::pair<std::string, std::string>(std::string("cco"),std::string("application/x-cocoa")));
	tmp->insert(std::pair<std::string, std::string>(std::string("jardiff"),std::string("application/x-java-archive-diff")));
	tmp->insert(std::pair<std::string, std::string>(std::string("jnlp"),std::string("application/x-java-jnlp-file")));
	tmp->insert(std::pair<std::string, std::string>(std::string("run"),std::string("application/x-makeself")));
	tmp->insert(std::pair<std::string, std::string>(std::string("pl"),std::string("application/x-makeself")));
	tmp->insert(std::pair<std::string, std::string>(std::string("pm"),std::string("application/x-perl")));
	tmp->insert(std::pair<std::string, std::string>(std::string("prc"),std::string("application/x-perl")));
	tmp->insert(std::pair<std::string, std::string>(std::string("pdb"),std::string("application/x-pilot")));
	tmp->insert(std::pair<std::string, std::string>(std::string("rar"),std::string("application/x-rar-compressed")));
	tmp->insert(std::pair<std::string, std::string>(std::string("rpm"),std::string("application/x-redhat-package-manager")));
	tmp->insert(std::pair<std::string, std::string>(std::string("sea"),std::string("application/x-sea")));
	tmp->insert(std::pair<std::string, std::string>(std::string("swf"),std::string("application/x-shockwave-flash")));
	tmp->insert(std::pair<std::string, std::string>(std::string("sit"),std::string("application/x-stuffit")));
	tmp->insert(std::pair<std::string, std::string>(std::string("tcl"),std::string("application/x-stuffit")));
	tmp->insert(std::pair<std::string, std::string>(std::string("tk"),std::string("application/x-tcl")));
	tmp->insert(std::pair<std::string, std::string>(std::string("der"),std::string("application/x-tcl")));
	tmp->insert(std::pair<std::string, std::string>(std::string("pem"),std::string("application/x-tcl")));
	tmp->insert(std::pair<std::string, std::string>(std::string("crt"),std::string("application/x-x509-ca-cert")));
	tmp->insert(std::pair<std::string, std::string>(std::string("xpi"),std::string("application/x-xpinstall")));
	tmp->insert(std::pair<std::string, std::string>(std::string("xhtml"),std::string("application/xhtml+xml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("xspf"),std::string("application/xspf+xml")));
	tmp->insert(std::pair<std::string, std::string>(std::string("zip"),std::string("application/zip")));
	tmp->insert(std::pair<std::string, std::string>(std::string("bin"),std::string("application/zip")));
	tmp->insert(std::pair<std::string, std::string>(std::string("exe"),std::string("application/zip")));
	tmp->insert(std::pair<std::string, std::string>(std::string("dll"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("deb"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("dmg"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("iso"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("img"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("msi"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("msp"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("msm"),std::string("application/octet-stream")));
	tmp->insert(std::pair<std::string, std::string>(std::string("docx"),std::string("application/vnd.openxmlformats-officedocument.wordprocessingml.document")));
	tmp->insert(std::pair<std::string, std::string>(std::string("xlsx"),std::string("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet")));
	tmp->insert(std::pair<std::string, std::string>(std::string("pptx"),std::string("application/vnd.openxmlformats-officedocument.presentationml.presentation")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mid"),std::string("application/vnd.openxmlformats-officedocument.presentationml.presentation")));
	tmp->insert(std::pair<std::string, std::string>(std::string("midi"),std::string("application/vnd.openxmlformats-officedocument.presentationml.presentation")));
	tmp->insert(std::pair<std::string, std::string>(std::string("kar"),std::string("audio/midi")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mp3"),std::string("audio/mpeg")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ogg"),std::string("audio/ogg")));
	tmp->insert(std::pair<std::string, std::string>(std::string("m4a"),std::string("audio/x-m4a")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ra"),std::string("audio/x-realaudio")));
	tmp->insert(std::pair<std::string, std::string>(std::string("3gpp"),std::string("audio/x-realaudio")));
	tmp->insert(std::pair<std::string, std::string>(std::string("3gp"),std::string("video/3gpp")));
	tmp->insert(std::pair<std::string, std::string>(std::string("ts"),std::string("video/mp2t")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mp4"),std::string("video/mp4")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mpeg"),std::string("video/mp4")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mpg"),std::string("video/mpeg")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mov"),std::string("video/quicktime")));
	tmp->insert(std::pair<std::string, std::string>(std::string("webm"),std::string("video/webm")));
	tmp->insert(std::pair<std::string, std::string>(std::string("flv"),std::string("video/x-flv")));
	tmp->insert(std::pair<std::string, std::string>(std::string("m4v"),std::string("video/x-m4v")));
	tmp->insert(std::pair<std::string, std::string>(std::string("mng"),std::string("video/x-mng")));
	tmp->insert(std::pair<std::string, std::string>(std::string("asx"),std::string("video/x-mng")));
	tmp->insert(std::pair<std::string, std::string>(std::string("asf"),std::string("video/x-ms-asf")));
	tmp->insert(std::pair<std::string, std::string>(std::string("wmv"),std::string("video/x-ms-wmv")));
	tmp->insert(std::pair<std::string, std::string>(std::string("avi"),std::string("video/x-msvideo")));
	return (tmp);
}