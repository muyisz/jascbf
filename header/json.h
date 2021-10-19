#pragma once
#include<stdarg.h>
#include<string>
#include<vector>
class json {
private:
	template<class key, class value, class ... Types>
	void init(key k, value val, Types...types) {
		con += typeToStr(k) + ":";
		con += typeToStr(val) + ",";
		init(types...);
	}
	void init();
	std::string typeToStr(std::string);
	std::string typeToStr(int);
	std::string typeToStr(const char*);
	std::string typeToStr(double);
	std::string typeToStr(bool);
	std::string typeToStr(std::vector<int>);
	std::string typeToStr(std::vector<std::string>);
public:
	template<class ... Types>
	json(Types... types) {
		con = "";
		con += "{";
		init(types...);
		con.pop_back();
		con += "}";
	}
	int getSize();
	std::string getTe();
private:
	std::string con;
};

