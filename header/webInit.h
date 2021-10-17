#pragma once
#include<thread>
#include<WinSock2.h>
#include <Windows.h>
#include "handller.h"
#include <iostream>
#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <iostream>
#include <stdexcept>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using HOST = int;
extern class threadPool;

const int msgSize = 10240;

class webInit
{
public:
	webInit(HOST, handller&);
	~webInit();
	void lis();
	void conversation(SOCKET);
private:
	threadPool *tPool;
	HOST host;
	SOCKET sListen;
	handller handler;
};
