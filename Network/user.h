#pragma once
#include "Connection.h"
#include "file.h"
namespace Network {

	class User
	{
	public:
		User(connection_ptr con, std::string username);
		~User();
		void download_file(File* file);


	private:
		connection_ptr m_connection;
		std::string m_name;
	};

}