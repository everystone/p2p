#include "stdafx.h"
#include "client.h"


void iorun(boost::asio::io_service * ios)
{
	ios->run();
	//std::cout << "io ended" << std::endl;
}

Client::Client(short port, ICallbacks* cb)
{
	this->m_callbacks = cb;
	this->listen(port);
}


bool Client::listen(short port)
{
	try {

		m_router.serve(io, port, this->m_callbacks);
		boost::thread t(boost::bind(&iorun, &io));
		//std::cout << "Server listening on 2222.\n";
	}
	catch (std::exception& e) {
		//std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

bool Client::connect(const char* ip, short port)
{
	return this->m_router.open(this->io, ip, port);
}

/// Send Ping packet to all sockets
void Client::ping()
{
	this->m_router.ping();
}


Client::~Client()
{

}

