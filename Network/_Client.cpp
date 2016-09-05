// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "router.h"
#include <boost/thread/thread.hpp>


void iorun2(boost::asio::io_service * ios)
{
	ios->run();
	std::cout << "io ended" << std::endl;
}

int main()
{
	boost::asio::io_service io;
	Network::Router router;
	try {
		router.serve(io, 2222, nullptr);
		boost::thread t(boost::bind(&iorun2, &io));
		std::cout << "Server listening on 2222.\n";
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}


	router.open(io, "127.0.0.1", 2222);
	std::cin.get();
	return 0;
}

