#ifndef TCP_IP_client_h
#define TCP_IP_client_h
#endif 
#include "TCP_IP.h"
#pragma once 

class TCP_IP_client : public TCP_IP
{
public:
	TCP_IP_client();

	void initWinSocket();
	void createSocket();
	void connectServer();
	void sendData(std::string data, int size);
	int getSendResult();
	SOCKET getSocket();
private:
	int sendResult;
	int wsResult;
	int connectResult;
	SOCKET sock;
	sockaddr_in hint;
};