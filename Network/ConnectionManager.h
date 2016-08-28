#pragma once
#include <map>
#include "Connection.h"

class ConnectionManager
{
public:

	 static void Add(connection_ptr con);
	 static std::list<connection_ptr> Connections;
	//static Connection Get(int index);
private:

	//static std::map<int, Connection::pointer> Connections;
	
	

};

