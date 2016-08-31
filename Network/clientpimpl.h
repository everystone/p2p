#pragma once
#include "typedefs.h"
class Client;

class ClientPimpl
{
public:
	ClientPimpl(short port, ICallbacks* cb);
	~ClientPimpl();
	bool Listen(short port);
	bool Connect(char* ip, short port);


private:
	Client *client;
};

