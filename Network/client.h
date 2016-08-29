#pragma once
#include "router.h"
#include <boost/thread/thread.hpp>
#include "typedefs.h"

//struct dataEvent {
//	char id;
//	std::string data;
//};

//typedef void (__stdcall * PFOnEventCallback)(dataEvent);


class Client
{
public:
	Client(short port);
	bool Listen(short port);
	bool Connect(char* ip, short port);

	void set_progress_delegate(ProgressDelegate progress);

	// https://msdn.microsoft.com/en-us/library/ee2k0a7d.aspx
	//void(*OnConnected)(void);
	//void(*OnDisconnected)(void);

	~Client();

private:
	void setup_callbacks();
	boost::asio::io_service io;
	Network::Router router;
	//PFOnEventCallback m_fireEvent;
	tProgressDelegate *progress;
	

	
};

