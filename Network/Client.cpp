#include "stdafx.h"
#include "client.h"

namespace Network {


	void iorun(boost::asio::io_service * ios)
	{
		ios->run();
		//std::cout << "io ended" << std::endl;
	}

	Client::Client(short port)
	{
		this->Listen(port);
	}

	Client::Client()
	{

	}

	bool Client::Listen(short port)
	{
		try {

			router.Serve(io, port);
			boost::thread t(boost::bind(&iorun, &io));
			//std::cout << "Server listening on 2222.\n";
		}
		catch (std::exception& e) {
			//std::cerr << e.what() << std::endl;
			return false;
		}
		return true;
	}

	bool Client::Connect(std::string ip, short port)
	{
		return this->router.Open(this->io, ip, port);
	}

	Client::~Client()
	{

	}
}