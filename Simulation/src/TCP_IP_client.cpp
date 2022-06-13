#include "TCP_IP_client.h"

TCP_IP_client::TCP_IP_client() {}


void TCP_IP_client::initWinSocket()
{
	wsResult = WSAStartup(version, &wsData);
	if (wsResult != 0)
	{
		std::cerr << "Winsocket cannot be initialized(" <<wsResult<< ")" << std::endl;
		return;
	}
}

void TCP_IP_client::createSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Socket cannot be created( " << WSAGetLastError() << " )" << std::endl;
		WSACleanup();
		return; 
	}
	//Fill in hint
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, IPAddress.c_str(), &hint.sin_addr); 
}

void TCP_IP_client::connectServer()
{
	connectResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectResult == SOCKET_ERROR)
	{
		std::cerr << "Cannot connect to server ( " << WSAGetLastError() << " )" << std::endl;
		closesocket(sock);
		WSACleanup();
		return; 
	}
}
void TCP_IP_client :: sendData(std::string data, int size)
{
	sendResult = send(sock, data.c_str(), size, 0);
}

int TCP_IP_client::getSendResult()
{
	return sendResult;
}

SOCKET TCP_IP_client::getSocket()
{
	return sock;
}



