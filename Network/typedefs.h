#pragma once
//typedef void tProgressDelegate(double);
//typedef tProgressDelegate *ProgressDelegate;

//typedef void(__stdcall *SampleTimeChangedCallback)(SampleTime sampleTime);
typedef void(__stdcall *ProgressDelegate)(double value);