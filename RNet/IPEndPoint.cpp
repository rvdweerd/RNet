#include "IPEndPoint.h"
#include <string>
#include <WS2tcpip.h>

RNet::IPEndPoint::IPEndPoint(const char* ip, unsigned short port)
	//:
	//port(port),
	//ip_string(ip)
{
	this->port = port;
	in_addr addr; //location to store the ipv4 address
	int result = inet_pton(AF_INET,ip,&addr); // from presentation format (e.g. "127.0.0.1") to network format (in bytes)
	if (result == 1)
	{
		if (addr.S_un.S_addr != INADDR_NONE)
		{
			ip_string = ip;
			hostname = ip;// ip entered, not a hostname
			ip_bytes.resize(sizeof(ULONG));
			memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(ULONG)); //[0] can be left out?
			ipversion = IPVersion::IPv4;
			return;
		}
	}
}

RNet::IPVersion RNet::IPEndPoint::GetIPVersion()
{
	return ipversion;
}

std::vector<uint8_t> RNet::IPEndPoint::GetIPBytes()
{
	return ip_bytes;
}

std::string RNet::IPEndPoint::GetHostName()
{
	return hostname;
}

std::string RNet::IPEndPoint::GetIPString()
{
	return ip_string;
}

unsigned short RNet::IPEndPoint::GetPort()
{
	return port;
}
