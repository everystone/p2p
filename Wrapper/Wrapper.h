// Wrapper.h

#pragma once
#include "clientpimpl.h"

#pragma 
using namespace System;

namespace NetworkWrapper {

	public ref class NetworkWrapper
	{

	public:
		NetworkWrapper() {}
		NetworkWrapper(short port) {
			_client = new ClientPimpl(port);
		}


	private:
		ClientPimpl *_client;
		bool Connect(String ^ip, short port) {
			return _client->Connect((char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(ip).ToPointer(), port);
		}
		bool Listen(short port) {
			return _client->Listen(port);
		}

	};
}
