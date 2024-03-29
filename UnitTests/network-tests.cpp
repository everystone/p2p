
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Network\client.h"
#include "..\Network\typedefs.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{

	class Cb : public ICallbacks {
		// Inherited via ICallbacks
	public:
		virtual void OnConnect(std::string) override
		{
			this->connected = true;
		}
		virtual void OnDisconnect(std::string) override
		{
			this->connected = false;
		}
		virtual void OnError(std::string) override
		{
			this->errors++;
		}
		virtual void OnListen(short port) override {
			this->listening = true;
		}
		virtual void OnSend(int mType) override {
			this->sent++;
		}
		virtual void OnReceive(int mType) override {
			this->received++;
		}
		bool connected,listening = false;
		int errors, connections = 0;
		int sent, received = 0;
	};


	// https://msdn.microsoft.com/en-us/library/hh694604.aspx
	TEST_CLASS(network)
	{
	public:
		static Client* client;
		static Client* client2;
		static Cb cb, cb2;

		TEST_CLASS_INITIALIZE(setup) {
			
			client = new Client(2222, &cb);
			client2 = new Client(2225, &cb2);
			Assert::IsTrue(cb.listening);
			Assert::IsTrue(cb2.listening);
			client->connect("127.0.0.1", 2225);
			Sleep(50);
			Assert::IsTrue(cb.connected);
			Assert::IsTrue(cb2.connected);
		}
		TEST_CLASS_CLEANUP(cleanup) {
			client->stop();
			client2->stop();
		}


		TEST_METHOD(send_receive)
		{
			Assert::AreEqual(0, cb.sent);

			client->ping();
			Sleep(50);
			Assert::AreEqual(1, cb.sent);		// sent ping
			Assert::AreEqual(1, cb2.received);	// received ping
			Assert::AreEqual(1, cb2.sent);		// sent pong
			Assert::AreEqual(1, cb.received);	// received pong
		}

		TEST_METHOD(file_transfers) {
			
		}
	};

	Client* network::client = NULL;
	Client* network::client2 = NULL;
	Cb network::cb, network::cb2;


}