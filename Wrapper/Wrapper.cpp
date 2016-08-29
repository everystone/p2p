// This is the main DLL file.

#include "stdafx.h"

#include "Wrapper.h"
// https://nicoschertler.wordpress.com/2013/02/18/allow-native-c-components-to-raise-clr-events/#comment-924
namespace p2p {

	IntPtr fix(NetworkWrapper^ w, System::Delegate^ o) {

		GCHandle gch = GCHandle::Alloc(o);
		//Convert the delegate to a function pointer
		IntPtr ip = Marshal::GetFunctionPointerForDelegate(o);
		//... and cast it to the appropriate type
		return ip;
		//ProgressDelegate fp = static_cast<ProgressDelegate>(ip.ToPointer());
		//set the native function pointer on the native class
		//this->_client->set_progress_delegate(fp);
	}

	void NetworkWrapper::raiseProgressChangedEvent(double progress)
	{
		ProgressChanged(progress);
	}
	void NetworkWrapper::raiseConnectedEvent(String^ ip)
	{
		//String^ ms = Marshal::PtrToStringAnsi(static_cast<IntPtr>(ip));
		Connected(ip);
	}
	void NetworkWrapper::Initialize()
	{
		//Create a new delegate and point it to the member function
		CLRProgressDelegate^ prDel = gcnew CLRProgressDelegate(this, &NetworkWrapper::raiseProgressChangedEvent);
		CLRConnectedDelegate^ cDel = gcnew CLRConnectedDelegate(this, &NetworkWrapper::raiseConnectedEvent);
		

		ProgressDelegate fp = static_cast<ProgressDelegate>(fix(this, prDel).ToPointer());
		ConnectDelegate c = static_cast<ConnectDelegate>(fix(this, cDel).ToPointer());
		//set the native function pointer on the native class
		this->_client->set_progress_delegate(fp);
		this->_client->set_connect_delegate(c);
	}
}