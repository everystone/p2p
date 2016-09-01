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
	Client(short port, ICallbacks* cb);
	bool listen(short port);
	bool connect(const char* ip, short port);
	void ping();

	~Client();

private:
	boost::asio::io_service io;
	Network::Router m_router;
	ICallbacks* m_callbacks;
	//PFOnEventCallback m_fireEvent;
	

	
};

