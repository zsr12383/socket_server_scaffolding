#include "Server.h"
#include <iostream>

void Server::do_accept()
{
	acceptor_.async_accept(socket_,
	                       [this](const boost::system::error_code& ec)
	                       {
		                       if (!ec)
		                       {
			                       std::cout << "[system] User Join: " << std::endl;
			                       std::make_shared<ChatSession>(std::move(socket_), sessions_)->start();
		                       }
		                       do_accept();
	                       });
}
