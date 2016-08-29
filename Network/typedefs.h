#pragma once
#include <string>
//typedef void tProgressDelegate(double);
//typedef tProgressDelegate *ProgressDelegate;

//typedef void(__stdcall *SampleTimeChangedCallback)(SampleTime sampleTime);
typedef void(__stdcall *ProgressDelegate)(double value);
typedef void(__stdcall *ConnectDelegate)( std::string ip);