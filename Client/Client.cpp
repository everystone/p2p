// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "router.h"
#include <boost/thread/thread.hpp>


void iorun(boost::asio::io_service * ios)
{
	ios->run();
	std::cout << "io ended" << std::endl;
}

int main()
{
	boost::asio::io_service io;


	try {
		Router server;
		server.Serve(io, 2222);
		boost::thread t(boost::bind(&iorun, &io));
		std::cout << "Server listening on 2222.\n";
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	
	std::cin.get();
    return 0;
}

