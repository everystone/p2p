#pragma once
#include "typedefs.h"
class Client;

class ClientPimpl
{
public:
	ClientPimpl(short port);
	~ClientPimpl();
	bool Listen(short port);
	bool Connect(char* ip, short port);

	void set_progress_delegate(ProgressDelegate progress);
	void set_connect_delegate(ConnectDelegate connect);
	//void SetupEvents(void(*OnConnected)(void), void(*OnDisconnected)(void));

private:
	Client *client;
};

