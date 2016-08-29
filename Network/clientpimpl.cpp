#include "stdafx.h"
#include "clientpimpl.h"
#include "client.h"

ClientPimpl::ClientPimpl(short port)
{
	client = new Client(port);
}

ClientPimpl::ClientPimpl()
{
	client = new Client();
}

ClientPimpl::~ClientPimpl()
{
	delete client;
}

bool ClientPimpl::Listen(short port)
{
	return client->Listen(port);
}

bool ClientPimpl::Connect(char* ip, short port)
{
	return client->Connect(ip, port);
}
