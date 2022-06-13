#include "TCP_IP_server.h"


TCP_IP_Server::TCP_IP_Server() {}

void TCP_IP_Server::createSocket()
{
	winsok = WSAStartup(version, &wsData);
	if (winsok != 0)
	{
		std::cerr << "Winsocket couldn't be initialized" << std::endl;
	}
	socket_listening = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_listening == INVALID_SOCKET)
	{
		std::cerr << "Socket couldn't be created." << std::endl;
	}
}

void TCP_IP_Server::bindSocket()
{
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //Accept any IP
	if (bind(socket_listening, (sockaddr*)&hint, sizeof(hint)) < 0)
	{
		std::cerr << "Socket binding failed" << std::endl;
	}
}

void TCP_IP_Server::startListening()
{
	listen(socket_listening, SOMAXCONN); // This socket is reserved for listening
	acceptSize = sizeof(acceptAddr);
	socket_accept = accept(socket_listening, (sockaddr*)&acceptAddr, &acceptSize);
	memset(hostName, 0, NI_MAXHOST);
	memset(serviceName, 0, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&acceptAddr, sizeof(acceptAddr), hostName, NI_MAXHOST, serviceName, NI_MAXSERV, 0)==0)
	{
		std::cout << hostName << "connected to port: " << serviceName << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &acceptAddr.sin_addr, hostName, NI_MAXHOST);
		std::cout << hostName << " connected to port:  " << ntohs(acceptAddr.sin_port) << std::endl;
	}
	//close listening socket
	//closesocket(socket_listening);
}

void TCP_IP_Server::sendData(char message[], int size)
{
	send(socket_accept, message, size, 0);
}