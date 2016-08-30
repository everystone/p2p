#pragma once
#include "router.h"
#include <boost/thread/thread.hpp>
#include "typedefs.h"

//struct dataEvent {
//	char id;
//	std::string data;
//};

class Client
{
public:
	Client(short port);
	bool Listen(short port);
	bool Connect(char* ip, short port);

	//void set_progress_delegate(ProgressDelegate progress);
	void set_connect_delegate(ConnectCallback connect);


	~Client();

private:
	boost::asio::io_service io;
	Network::Router router;
	//PFOnEventCallback m_fireEvent;
	

	
};

