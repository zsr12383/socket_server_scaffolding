#include <iostream>
#include <boost/asio.hpp>
#include "Server.h"

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_service io_service;
		const tcp::endpoint endpoint(tcp::v4(), 3000);
		Server server(io_service, endpoint);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
