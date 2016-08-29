#pragma once
#include "router.h"
#include <boost/thread/thread.hpp>

class Client
{
public:
	Client(short port);
	Client();
	bool Listen(short port);
	bool Connect(char* ip, short port);

	~Client();

private:
	boost::asio::io_service io;
	Network::Router router;
};

