#include "stdafx.h"
#include "router.h"
#pragma warning(disable:4996)

namespace Network {

	// Opens a new connection to remote client
	bool Router::Open(boost::asio::io_service& io_service, const char* ip, short port)
	{
		try {
			//tcp::resolver resolver(io_service);
			//tcp::resolver::query query(ip, port);
			//tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			//tcp::socket socket(io_service);
			//socket.connect(*endpoint_iterator);
			boost::asio::ip::address_v4 ipaddr = boost::asio::ip::address_v4::from_string(ip);
			boost::asio::ip::tcp::endpoint ep(ipaddr, port);

			connection_ptr new_connection = Connection::create(this->m_acceptor->get_io_service());
			// Start an asynchronous connect operation.
			new_connection->socket().async_connect(ep,
				boost::bind(&Router::handle_connect, this,
					boost::asio::placeholders::error, ep, new_connection));
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
		return true;
	}

	void Router::handle_connect(const boost::system::error_code& e,
		boost::asio::ip::tcp::endpoint &endpoint,
		connection_ptr conn)
	{
		if (e) {
			std::cerr << "Failed to connect out to remote peer: " << e.message() << std::endl;
			return;
		}
		std::cout << "Connected to " << endpoint.address().to_string() << std::endl;
		//__raise this->ConnectEvent(endpoint.address().to_string());
		
		register_connection(conn);
		conn->async_read(); // start read loop for this connection
		//this->OnConnected(100);
	}


	void Router::handle_accept(connection_ptr new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			register_connection(new_connection);
			new_connection->start();

			if (this->Callbacks != nullptr) {
				this->Callbacks->OnConnect(new_connection->str());
			}
		}

		start_accept();
	}

	void Router::start_accept() {
		connection_ptr nConnection = Connection::create(this->m_acceptor->get_io_service());
		m_acceptor->async_accept(nConnection->socket(), boost::bind(&Router::handle_accept, this, nConnection, boost::asio::placeholders::error));
	}

	void Router::Serve(boost::asio::io_service& io_service, unsigned short port)
	{
		this->m_acceptor = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port));
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
}