#ifndef TCP_IP_h
#define TCP_IP_h

#include <iostream>
#include <ws2tcpip.h>
#include <cstring>
#pragma comment (lib, "ws2_32.lib")
#define PORT 54000					// Port of server
#define IP "192.168.80.107"		// IP of server

class TCP_IP
{
public:
	TCP_IP();
	WSAData wsData;
	WORD version;
	int winsok;
	std::string IPAddress = IP; 
	int port = PORT;


}; 

#endif	