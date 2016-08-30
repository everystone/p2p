#pragma once
#include <string>
#include <functional>
//typedef void tProgressDelegate(double);
//typedef tProgressDelegate *ProgressDelegate;

//typedef void(__stdcall *SampleTimeChangedCallback)(SampleTime sampleTime);
//typedef void(__stdcall *ProgressDelegate)(double value);
//typedef void(__stdcall *ConnectDelegate)( std::string ip);

//typedef void ConnectCallback(std::string ip);

typedef std::function<void(std::string)> ConnectCallback;
