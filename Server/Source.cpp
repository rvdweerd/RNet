// Server code
#include <RNet\IncludeMe.h>
#include <iostream>



int main()
{
	if (RNet::Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;

		RNet::IPEndPoint test("127.0.0.1", 8080);
		if (test.GetIPVersion() == RNet::IPVersion::IPv4)
		{
			std::cout << "Hostname: " << test.GetHostName()<<std::endl;
			std::cout << "IP: " << test.GetIPString() << std::endl;
			std::cout << "Port: " << test.GetPort() << std::endl;
			std::cout << "IP Bytes..." << std::endl;
			for (auto& digit : test.GetIPBytes())
			{
				std::cout << (int)digit << std::endl;
			}
		}
		else
		{
			std::cout << "This is not an IPv4 address." << std::endl;
		}

		RNet::Socket socket;
		if (socket.Create() == RNet::RResult::R_Success)
		{
			std::cout << "Socket successfully created.[SERVER]" << std::endl;
			socket.Close();
		}
		else
		{
			std::cout << "Socket failed to create." << std::endl;
		}
	}
	RNet::Network::Shutdown();
	system("pause");
	return 0;
}