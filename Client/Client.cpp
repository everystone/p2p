// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NetSocket.h"
int main()
{
	boost::asio::io_service io;


	try {
		NetSocket server;
		server.Serve(io, 2222);
		io.run();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cin.get();
    return 0;
}

