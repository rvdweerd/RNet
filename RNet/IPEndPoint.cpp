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
			memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(ULONG)); //could use ip_bytes.data() as well as first arg
			ipversion = IPVersion::IPv4;
			return;
		}
	}

	// Attempt to resolve hostname to ipv4 address
	addrinfo hints = {}; //hints will filter the results we get back for getaddrinfo
	addrinfo* hostinfo = nullptr;
	hints.ai_family = AF_INET; //ipv4 addresses only
	//hints.ai_socktype = SOCK_STREAM; //tcp
	//hints.ai_protocol = IPPROTO_TCP;
	result = getaddrinfo(ip, NULL, &hints, &hostinfo);
	if (result == 0)
	{
		sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr); // or cast using (sockaddr_in*); use sockaddr_in6 for ipv6
		
		ip_string.resize(16);
		inet_ntop(AF_INET, &host_addr->sin_addr, &ip_string[0], 16); // convert from network to presentation format
		//host_addr->sin_addr.S_un.S_un_b.s_b1;

		hostname = ip;
		ULONG ip_long = host_addr->sin_addr.S_un.S_addr;
		ip_bytes.resize(sizeof(ULONG));
		memcpy(&ip_bytes[0], &ip_long, sizeof(ULONG));

		ipversion = IPVersion::IPv4;
				
		freeaddrinfo(hostinfo);
		return;
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
