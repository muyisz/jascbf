#include "handller.h"
#include <iostream>
#include <fstream>

std::string intToStr(int n) {
	std::string c = "", d = "";
	while (n != 0) {
		c += n % 10 + '0';
		n /= 10;
	}
	for (int i = c.size() - 1; i >= 0; i--) {
		d += c[i];
	}
	return d;
}

handller::handller() {
	resourceCmp["js"] = " application/x-javascript";
	resourceCmp["html"] = " text/html";
	resourceCmp["XML"] = " text/xml";
	resourceCmp["gif"] = " image/gif";
	resourceCmp["jpg"] = " image/jpeg";
	resourceCmp["png"] = " image/png";
	resourceCmp["jfif"] = " image/jpeg";
}

std::string context::fromData(std::string name) {
	int loc = originalText.find(name);
	if (loc == std::string::npos) {
		return "";
	}
	loc += 5 + name.size();
	std::string ans = "";
	while (originalText[loc] != '\r') {
		ans += originalText[loc++];
	}
	return ans;
}

void context::HTML(int type, std::string fUrl) {
	con += "HTTP/1.0 ";
	con += intToStr(type) + " ";
	if (type == 200) {
		con += "OK\r\n";
	}
	con += "Content-Type: text/html\r\n";
	con += "Connection: keep-alive\r\n";
	con += "Content-Length: ";
	std::ifstream ifs(fUrl);
	std::string tmp((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	con += intToStr(tmp.size()) + "\r\n\r\n";
	con += tmp;
}

context::context(std::string ori) :originalText(ori) {
	con = "";
}

void context::JSON(int type, json& js) {
	con += "HTTP/1.0 ";
	con += intToStr(type) + " ";
	if (type == 200) {
		con += "OK\r\n";
	}
	con += "Content-Type: application/json\r\n";
	con += "Connection: keep-alive\r\n";
	con += "Content-Length: ";
	con += intToStr(js.getSize());
	con += "\r\n\r\n";
	con += js.getTe();
}

std::string context::getCon() {
	return con;
}

void handller::Get(std::string url, void (*profunc)(context*)) {
	getFunc[url] = profunc;
}

void handller::Post(std::string url, void (*profunc)(context*)) {
	postFunc[url] = profunc;
}

std::string handller::router(char* msg, int size) {
	std::string a;
	return  a;
}

std::string handller::getResource(std::string fUrl) {
	FILE* fp = nullptr;
	std::string con = "";
	fopen_s(&fp, fUrl.c_str() + 1, "r");
	for (int i = 0; i < fUrl.size(); i++) {
		if (fUrl[i] == '/')
			fUrl[i] = '\\';
	};
	if (fp == nullptr) {
		con += "HTTP/1.0 ";
		con += intToStr(404) + " ";
		con += "Not Found\r\n\r\n\r\n";
		return con;
	}
	fclose(fp);
	int loc = fUrl.find(".");
	loc++;
	std::string type = "";
	while (loc < fUrl.size()) {
		type += fUrl[loc++];
	}
	con += "HTTP/1.0 ";
	con += intToStr(200) + " ";
	con += "OK\r\n";
	con += "Content-Type:" + resourceCmp[type] + "\r\n";
	con += "Connection: keep-alive\r\n";
	con += "Content-Length: ";
	std::ifstream in(fUrl.c_str() + 1, std::ios::in | std::ios::binary);
	std::string tmp;
	in.seekg(0, std::ios::end);
	tmp.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&tmp[0], tmp.size());
	in.close();
	con += intToStr(tmp.size()) + "\r\n\r\n";
	con += tmp;
	return con;
}

std::string handller::pars(char* msg, int size) {
	std::string url = "";
	bool tag = 0;
	for (int i = 0; i < size; i++) {
		if (msg[i] == '/') {
			url += msg[i++];
			while (msg[i] != ' ') {
				url += msg[i++];
				if (msg[i] == '.')
					tag = 1;
			}
			break;
		}
	}
	if (tag == 1) {
		std::string c = getResource(url);
		return c;
	}
	if (msg[0] == 'G') {
		std::string s = msg;
		context* con = new context(msg);
		if (getFunc[url] == nullptr) {
			return "HTTP/1.0 404 Not Found\r\n\r\n\r\n";
		}
		getFunc[url](con);
		std::string c = con->getCon();
		delete con;
		return c;
	}
	else if (msg[0] == 'P') {
		std::string s = msg;
		context* con = new context(msg);
		if (postFunc[url] == nullptr) {
			return "HTTP/1.0 404 Not Found\r\n\r\n\r\n";
		}
		postFunc[url](con);
		std::string c = con->getCon();
		delete con;
		return c;
	}
	else {
		return "HTTP/1.0 404 Not Found\r\n\r\n\r\n";
	}
}
