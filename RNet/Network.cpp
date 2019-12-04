#include "Network.h"
#include <iostream>

bool RNet::Network::Initialize()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int result;

	wVersionRequested = MAKEWORD(2, 2);
	result = WSAStartup(wVersionRequested, &wsaData);

	if (result != 0)
	{
		std::cerr << "Failed to start up the winsock API." << std::endl;
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		std::cerr << "Could not find a usable version of the winsock api dll." << std::endl;
		return false;
	}
	return true;
}

void RNet::Network::Shutdown()
{
	WSACleanup();
}
