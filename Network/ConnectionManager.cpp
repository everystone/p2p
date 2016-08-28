#include "stdafx.h"
#include "ConnectionManager.h"

// Initialize Static member...
std::list<boost::shared_ptr<Connection>> ConnectionManager::Connections = {};

void ConnectionManager::Add(connection_ptr con)
{
	//Connections.emplace(con);
	ConnectionManager::Connections.push_back(con);
}

//Connection ConnectionManager::Get(int index)
//{
//	return Connections.at(index);
//}
