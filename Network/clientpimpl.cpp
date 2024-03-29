#include "stdafx.h"
#include "clientpimpl.h"
#include "client.h"

ClientPimpl::ClientPimpl(short port, ICallbacks* cb)
{
	client = new Client(port, cb);
}


ClientPimpl::~ClientPimpl()
{
	delete client;
}

bool ClientPimpl::Listen(short port)
{
	return client->listen(port);
}

bool ClientPimpl::Connect(char* ip, short port)
{
	return client->connect(ip, port);
}

//void ClientPimpl::set_progress_delegate(ProgressDelegate progress) {
//	client->set_progress_delegate(progress);
//}
//
//void ClientPimpl::set_connect_delegate(ConnectDelegate connect)
//{
//	client->set_connect_delegate(connect);
//}

//void ClientPimpl::SetupEvents(void(*OnConnected)(void), void(*OnDisconnected)(void))
//{
//	if (client) {
//		client->OnConnected = OnConnected;
//		client->OnDisconnected = OnDisconnected;
//	}
//}
