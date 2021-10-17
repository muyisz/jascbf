#include "webInit.h"
#include<stdio.h>
#include"threadPool.h"

webInit::webInit(HOST host, handller& han) :handler(han) {
	this->host = host;
	tPool = new threadPool(16);
}

webInit::~webInit() {
}

void webInit::lis() {
	WSADATA wsaData;
	SOCKET sClient;
	SOCKADDR_IN local;
	SOCKADDR_IN client;
	int ret;
	int iaddrSize = sizeof(SOCKADDR_IN);
	WSAStartup(0x0202, &wsaData);
	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	local.sin_family = AF_INET;
	local.sin_port = htons(host);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sListen, (struct sockaddr*)&local, sizeof(SOCKADDR_IN));
	listen(sListen, 1);
	while (true) {
		SOCKET sClient;
		sClient = accept(sListen, (struct sockaddr*)&client, &iaddrSize);
		SOCKET* s = new SOCKET(std::move(sClient));
		tPool->commit(&webInit::conversation, *s, (this));
	}
}

void webInit::conversation(SOCKET msg) {
	char* szMessage = new char[msgSize];
	while (true) {
		int size = 0;
		size = recv(msg, szMessage, msgSize, 0);
		szMessage[size] = '\0';
		std::string con = handler.pars(szMessage, size);
		if (con != "") {
			int type = send(msg, con.c_str(), con.size(), 0);
		}
		if (con.find("404") != std::string::npos)
			break;
	}
	delete[]szMessage;
	szMessage = nullptr;
	closesocket(msg);
}