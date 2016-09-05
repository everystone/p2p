#pragma once
#include <string>
#include <functional>
//typedef void tProgressDelegate(double);
//typedef tProgressDelegate *ProgressDelegate;

//typedef void(__stdcall *SampleTimeChangedCallback)(SampleTime sampleTime);
//typedef void(__stdcall *ProgressDelegate)(double value);
typedef void(*ConnectCallback)( std::string ip);

class ICallbacks
{
public:
	virtual void OnConnect(std::string) = 0;
	virtual void OnDisconnect(std::string) = 0;
	virtual void OnError(std::string) = 0;
	virtual void OnListen(short port) = 0;
	// for unit tests.
	virtual void OnReceive(int mType) = 0;
	virtual void OnSend(int mType) = 0;
};

//typedef void ConnectCallback(std::string ip);

//typedef std::function<void(std::string)> ConnectCallback;
