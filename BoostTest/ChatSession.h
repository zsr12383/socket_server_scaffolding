#pragma once
#include <boost/asio.hpp>
using boost::asio::ip::tcp;


class ChatSession : public std::enable_shared_from_this<ChatSession>
{
public:
	ChatSession(tcp::socket socket, std::vector<std::shared_ptr<ChatSession>>& sessions)
		: socket_(std::move(socket)), sessions_(sessions)
	{
	}

	void start();

	void do_read();

	void do_write(const std::string& message);

	void broadcast(const std::string& message);

private:
	tcp::socket socket_;
	boost::asio::streambuf buffer_;
	std::vector<std::shared_ptr<ChatSession>>& sessions_;
};
