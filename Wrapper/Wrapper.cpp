// This is the main DLL file.

#include "stdafx.h"

#include "Wrapper.h"
namespace p2p {
	void NetworkWrapper::raiseProgressChangedEvent(double progress)
	{
		ProgressChanged(progress);
	}
	void NetworkWrapper::Initialize()
	{
		//Create a new delegate and point it to the member function
		CLRProgressDelegate^ prDel = gcnew CLRProgressDelegate(this, &NetworkWrapper::raiseProgressChangedEvent);
		GCHandle gch = GCHandle::Alloc(prDel);
		//Convert the delegate to a function pointer
		IntPtr ip = Marshal::GetFunctionPointerForDelegate(prDel);
		//... and cast it to the appropriate type
		ProgressDelegate fp = static_cast<ProgressDelegate>(ip.ToPointer());
		//set the native function pointer on the native class
		this->_client->set_progress_delegate(fp);
	}
}