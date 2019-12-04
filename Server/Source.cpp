// Server code
#include <RNet\IncludeMe.h>
#include <iostream>



int main()
{
	if (RNet::Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
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