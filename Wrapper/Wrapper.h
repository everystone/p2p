// Wrapper.h

#pragma once
#include "client.h"

#pragma 
using namespace System;

namespace NetworkWrapper {

	ref class NetworkWrapper
	{
	private:
		Network::Client *_client;
		NetworkWrapper() {}
		NetworkWrapper(short port) {
			_client = new Network::Client(port);
		}
		bool Connect(String ^ip, short port) {
			return _client->Connect((char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(ip).ToPointer(), port);
		}
		bool Listen(short port) {
			return _client->Listen(port);
		}

	};
}
