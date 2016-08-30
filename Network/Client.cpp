#include "stdafx.h"
#include "client.h"


void iorun(boost::asio::io_service * ios)
{
	ios->run();
	//std::cout << "io ended" << std::endl;
}

Client::Client(short port)
{
	this->Listen(port);

	// Hookup events
	//__hook(&Network::Router::ConnectEvent, &this->router, &Client::OnConnected);
	//__hook(&Network::Router::DisconnectEvent, &this->router, &Client::OnDisconnected);
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

bool Client::Connect(char* ip, short port)
{
	return this->router.Open(this->io, ip, port);
}

//void Client::set_progress_delegate(ProgressDelegate progress)
//{
//	//this->router.OnConnected = progress;
//	std::cout << "Registered progress delegate: " << progress << std::endl;
//}
void Client::set_connect_delegate(ConnectCallback connect)
{
	this->router.OnConnected = connect;
}

Client::~Client()
{

}

