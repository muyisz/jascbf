#pragma once
#include<string>
#include<map>
#include"json.h"
const int httpOK = 200;

class context
{
public:
	context(std::string orig);
	void HTML(int, std::string);
	void JSON(int, json&);
	std::string getCon();
	std::string fromData(std::string);
private:
	std::string con;
	std::string originalText;
};

class handller
{
public:
	handller();
	void Get(std::string, void (*profunc)(context*));
	void Post(std::string, void (*profunc)(context*));
	std::string pars(char*, int);
	std::string router(char*, int);
	std::string getResource(std::string);
private:
	std::map<std::string, void (*)(context*)>getFunc;
	std::map<std::string, void (*)(context*)>postFunc;
	std::map<std::string, std::string>resourceCmp;
};