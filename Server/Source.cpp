// Server code
#include <RNet\IncludeMe.h>
#include <iostream>



int main()
{
	if (RNet::Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
	}
	RNet::Network::Shutdown();
	system("pause");
	return 0;
}