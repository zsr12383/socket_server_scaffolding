#include "ChatSession.h"
#include <iostream>

void ChatSession::start()
{
	sessions_.push_back(shared_from_this());
	do_read();
}

void ChatSession::do_read()
{
	auto self(shared_from_this());
	boost::asio::async_read_until(socket_, buffer_, '\n',
	                              [this, self](const boost::system::error_code& ec, const std::size_t bytes_transferred)
	                              {
		                              if (!ec)
		                              {
			                              const auto message = std::string(
				                              boost::asio::buffers_begin(buffer_.data()),
				                              boost::asio::buffers_begin(buffer_.data()) + bytes_transferred);
			                              std::cout << "Received message: " << message << std::endl;
			                              broadcast(message);
			                              do_read();
		                              }
	                              });
}

void ChatSession::do_write(const std::string& message)
{
	auto self(shared_from_this());
	boost::asio::async_write(socket_, boost::asio::buffer(message),
	                         [this, self](const boost::system::error_code& ec, std::size_t bytes_transferred)
	                         {
		                         if (ec)
		                         {
			                         std::cerr << "Failed to write to socket" << std::endl;
		                         }
	                         });
}

void ChatSession::broadcast(const std::string& message)
{
	for (auto& session : sessions_)
	{
		if (session != shared_from_this())
		{
			session->do_write(message);
		}
	}
}
