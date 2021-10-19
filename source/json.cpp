#include "json.h"

void json::init() {
	return;
}

int json::getSize() {
	return con.length();
}

std::string json::getTe() {
	return con;
}

std::string json::typeToStr(std::string t) {
	std::string c("\"");
	c += t;
	c += "\"";
	return std::string(c);
}

std::string json::typeToStr(int t) {
	std::string c(std::to_string(t));
	return c;
}

std::string json::typeToStr(const char* t) {
	std::string c("\"");
	c += t;
	c += "\"";
	return c;
}

std::string json::typeToStr(double t) {
	std::string c(std::to_string(t));
	return c;
}

std::string json::typeToStr(std::vector<int> t) {
	std::string c = "";
	c += "[";
	for (int i = 0; i < t.size(); i++) {
		c += typeToStr(t[i]);
		c += ",";
	}
	c.pop_back();
	c += "]";
	return c;
}

std::string json::typeToStr(std::vector<std::string> t) {
	std::string c = "";
	c += "[";
	for (int i = 0; i < t.size(); i++) {
		c += typeToStr(t[i]);
		c += ",";
	}
	c.pop_back();
	c += "]";
	return c;
}

std::string json::typeToStr(bool t) {
	if (t)
		return "true";
	else
		return "false";
}