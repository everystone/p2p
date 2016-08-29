// Wrapper.h

#pragma once
#include "clientpimpl.h"
#include "typedefs.h"

#pragma 
using namespace System;
using namespace System::Runtime::InteropServices;

namespace p2p {

	public delegate void CLRConnectedDelegate(String^ ip);
	public delegate void CLRProgressDelegate(double progress);
	public ref class NetworkWrapper
	{

	public:
		event CLRProgressDelegate^ ProgressChanged;
		event CLRConnectedDelegate^ Connected;
		void raiseProgressChangedEvent(double progress);
		void raiseConnectedEvent(String^ ip);

		NetworkWrapper(short port) {
			_client = new ClientPimpl(port);
			Initialize();
		}


	private:
		void Initialize();
		ClientPimpl *_client;
		bool Connect(char* ip, short port) {
			//return _client->Connect((char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(ip).ToPointer(), port);
			return _client->Connect(ip, port);
		}
		bool Listen(short port) {
			return _client->Listen(port);
		}

	};
}