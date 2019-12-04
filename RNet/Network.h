#pragma once
#define WIN32_LEAN_AND_MEAN // eliminates unused parts of the api
#include <WinSock2.h>

namespace RNet
{
	class Network
	{
	public:
		static bool Initialize();
		static void Shutdown();
	};
}
