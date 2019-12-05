#include "Socket.h"
#include <assert.h>
#include <iostream>
//#include "SocketHandle.h"
//#include "RResult.h"
//#include "IPVersion.h"

namespace RNet
{
	Socket::Socket(IPVersion ipversion, SocketHandle handle)
		:
		ipversion(ipversion),
		handle(handle)
	{
		assert(ipversion == IPVersion::IPv4);
	}

	RResult Socket::Create()
	{
		assert(ipversion == IPVersion::IPv4);
		if (handle != INVALID_SOCKET) //shouldn't initialize the socket if it has already been created
		{
			return RResult::R_NotYetImplemented; 
		}
		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // attempt to create socket; we use IPv4, tcp protocol, 
		if (handle == INVALID_SOCKET)
		{
			int  error = WSAGetLastError();
			return RResult::R_NotYetImplemented;
		}
		if (SetSocketOption(RNet::SocketOption::TCP_NoDelay, TRUE) != RNet::RResult::R_Success)
		{
			return RNet::RResult::R_NotYetImplemented;
		}
		std::cout << "Socket option set to TCP_NODELAY = TRUE.\n";
		return RResult::R_Success;
	}

	RResult Socket::Close()
	{
		if (handle == INVALID_SOCKET)
		{
			return RResult::R_NotYetImplemented;
		}
		int result = closesocket(handle);
		if (result != 0)
		{
			int error = WSAGetLastError();
			return RResult::R_NotYetImplemented;
		}
		handle = INVALID_SOCKET;
		return RResult::R_Success;
	}

	SocketHandle Socket::GetHandle()
	{
		return handle;
	}

	IPVersion Socket::GetIPVersion()
	{
		return ipversion;
	}
	RResult Socket::SetSocketOption(SocketOption option, BOOL value)
	{
		int result = 0;
		switch (option)
		{
		case SocketOption::TCP_NoDelay:
			result = setsockopt(handle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(value));
			break;
		default:
			return RResult::R_NotYetImplemented;
		}

		if (result != 0) // if an error occured
		{
			int error = WSAGetLastError();
			return RResult::R_NotYetImplemented;
		}
		return RResult::R_Success;
	}
}