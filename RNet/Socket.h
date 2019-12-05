#pragma once
#include "SocketHandle.h"
#include "RResult.h"
#include "IPVersion.h"
#include "SocketOptions.h"

namespace RNet
{
	class Socket
	{
	public:
		Socket(	IPVersion ipversion = IPVersion::IPv4,
				SocketHandle handle = INVALID_SOCKET);
		RResult Create();
		RResult Close();
		SocketHandle GetHandle();
		IPVersion GetIPVersion();

	private:
		RResult SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}
