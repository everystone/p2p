// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "router.h"
int main()
{
	boost::asio::io_service io;


	try {
		Router server;
		server.Serve(io, 2222);
		std::cout << "Server listening on 2222.\n";
		io.run();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	
	//std::cin.get();
    return 0;
}

