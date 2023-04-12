#pragma once
#include <boost/asio.hpp>
#include "ChatSession.h"
using boost::asio::ip::tcp;

class Server
{
public:
	Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
		: acceptor_(io_service, endpoint), socket_(io_service)
	{
		do_accept();
	}

private:
	void do_accept();

	tcp::acceptor acceptor_;
	tcp::socket socket_;
	std::vector<std::shared_ptr<ChatSession>> sessions_;
};
