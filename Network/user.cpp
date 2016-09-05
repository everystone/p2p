#include "stdafx.h"
#include "user.h"

namespace Network {

	User::User(connection_ptr con, std::string username)
	{
		this->m_connection = con;
		this->m_name = username;
	}

	
	User::~User()
	{
		// close connection?..
	}
	void User::download_file(File * file)
	{
		// 1. send FileRequestPacket
		//m_connection->do_write()

		// 2. in router onReceive, if a FileMetaPacket arrives, read size and start receiving until size is downloaded, then write to file?..

		// 3. after file downloaded, close socket?..
	}
}