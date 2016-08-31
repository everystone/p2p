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
	this->Listen(port);
}


bool Client::Listen(short port)
{
	try {

		m_router.Serve(io, port, this->m_callbacks);
		boost::thread t(boost::bind(&iorun, &io));
		//std::cout << "Server listening on 2222.\n";
	}
	catch (std::exception& e) {
		//std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

bool Client::Connect(char* ip, short port)
{
	return this->m_router.Open(this->io, ip, port);
}


Client::~Client()
{

}

