#include "stdafx.h"
#include "router.h"
#include "ConnectionManager.h"
#pragma warning(disable:4996)

void Router::Open(boost::asio::io_service& io_service, std::string ip, std::string port)
{
	try {
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ip, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(io_service);
		//socket.connect(*endpoint_iterator);
		boost::asio::connect(socket, endpoint_iterator);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cin.get();
	}
	std::cout << "Connected to " << ip << ":" << port << std::endl;
}


void Router::handle_accept(connection_ptr new_connection,
	const boost::system::error_code& error)
{
	if (!error)
	{
		register_connection(new_connection);
		new_connection->start();
	}

	start_accept();
}

void Router::start_accept() {
	connection_ptr nConnection = Connection::create(this->_acceptor->get_io_service());
	_acceptor->async_accept(nConnection->socket(), boost::bind(&Router::handle_accept, this, nConnection, boost::asio::placeholders::error));
}

void Router::Serve(boost::asio::io_service& io_service, unsigned short port)
{
	this->_acceptor = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port));
	start_accept();
	
}

void Router::register_connection(connection_ptr con)
{
	m_connections.push_back(con);
}




std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

void Router::Close()
{
}