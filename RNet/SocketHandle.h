#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

namespace RNet
{
	typedef SOCKET SocketHandle; //port to linux (uses integers), this way we can reference both
}