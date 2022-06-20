#ifndef TCP_IP_server_h
#define TCP_IP_server_h
#endif 
#include "TCP_IP.h"
#pragma once

class TCP_IP_Server : public TCP_IP
{
public:
	TCP_IP_Server();
	SOCKET socket_listening; //Socket for listening
	SOCKET socket_accept; //Socket for accepting the handshakes etc.
	sockaddr_in hint;
	sockaddr_in acceptAddr;
	int acceptSize;
	void createSocket();
	void bindSocket();
	void startListening();
	void sendData(char message[], int size);
private:
	char hostName[NI_MAXHOST];
	char serviceName[NI_MAXHOST];
};
