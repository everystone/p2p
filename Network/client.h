#pragma once
#include "router.h"
#include <boost/thread/thread.hpp>
namespace Network {
	class Client
	{
	public:
		Client(short port);
		Client();
		bool Listen(short port);
		bool Connect(std::string ip, short port);

		~Client();

	private:
		boost::asio::io_service io;
		Router router;
	};

}