#pragma once
#include <map>
#include "Connection.h"

class ConnectionManager
{
public:

	 static void Add(Connection::pointer con);
	 static std::list<Connection::pointer> Connections;
	//static Connection Get(int index);
private:

	//static std::map<int, Connection::pointer> Connections;
	
	

};

