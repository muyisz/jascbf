#pragma once
#include<string>
class ParseHttp {
public:
	ParseHttp(char*, int);
	std::string getUrl();
private:
	std::string Url;
	std::string Accept;
	std::string	Accept_Charset;
	std::string Accept_Encoding;
	std::string Accept_Language;
	std::string Authorization;
	std::string Connection;
	std::string Content_Length;
	std::string Cookie;
	std::string From;
	std::string Host;
	std::string If_Modified_Since;
	std::string Pragma;
	std::string Referer;
	std::string User_Agent;
};

