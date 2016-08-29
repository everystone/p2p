#pragma once

class Client;

class ClientPimpl
{
public:
	ClientPimpl(short port);
	ClientPimpl();
	~ClientPimpl();
	bool Listen(short port);
	bool Connect(char* ip, short port);

private:
	Client *client;
};

