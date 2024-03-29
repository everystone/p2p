#include "stdafx.h"
#include "router.h"
#include "messages.h"
#include <boost/foreach.hpp>
#pragma warning(disable:4996)

namespace Network {
	// Opens a new connection to remote client
	bool Router::open(boost::asio::io_service& io_service, const char* ip, short port)
	{
		
		try {
			boost::asio::ip::address_v4 ipaddr = boost::asio::ip::address_v4::from_string(ip);
			boost::asio::ip::tcp::endpoint ep(ipaddr, port);

			connection_ptr new_connection = Connection::create(this->m_acceptor->get_io_service(), this, this->m_callbacks);
			// Start an asynchronous connect operation.
			std::cout << "Connecting to " << ip << std::endl;
			new_connection->socket().async_connect(ep,
				boost::bind(&Router::handle_connect, this,
					boost::asio::placeholders::error, ep, new_connection));
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			std::stringstream err;
			err << "Connection failed: " << e.what() << std::endl;
			this->m_callbacks->OnError(err.str());
			return false;
		}
		return true;
	}
	std::string Router::uuid()
	{
		return boost::uuids::to_string(this->generator());
	}
	// outbound connection
	void Router::handle_connect(const boost::system::error_code& e, boost::asio::ip::tcp::endpoint &endpoint, connection_ptr conn)
	{
		if (e) {
			std::stringstream err;
			err << "Failed to connect out to remote peer: " << e.message() << std::endl;
			this->m_callbacks->OnError(err.str());
			return;
		}
		std::cout << "Connected to " << endpoint.address().to_string() << std::endl;
		register_connection(conn);
		conn->start();
	}

	void Router::handle_disconnect(connection_ptr conn)
	{
		unregister_connection(conn);
		this->m_callbacks->OnDisconnect(conn->str());
	}

	// inbound connection
	void Router::handle_accept(connection_ptr new_connection, const boost::system::error_code& error)
	{
		if (!error)
		{
			register_connection(new_connection);
			new_connection->start();
		}

		start_accept();
	}

	void Router::start_accept() {
		connection_ptr nConnection = Connection::create(this->m_acceptor->get_io_service(), this, this->m_callbacks);
		m_acceptor->async_accept(nConnection->socket(), boost::bind(&Router::handle_accept, this, nConnection, boost::asio::placeholders::error));
	}

	void Router::serve(boost::asio::io_service& io_service, unsigned short port, ICallbacks* cb)
	{
		this->m_io = &io_service;
		this->m_callbacks = cb;
		this->m_acceptor = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port));
		start_accept();
		this->m_callbacks->OnListen(port);
	}

	void Router::message_received(message_ptr msgp, connection_ptr conn)
	{
		this->m_callbacks->OnReceive(msgp->type());
		switch (msgp->type()) {
		case PING:
			std::cout << "got ping from " << conn->str() << std::endl;
			conn->do_write(message_ptr(new PongMessage(this->uuid())));
			//this->m_io->post(boost::bind(&Connection::do_write, conn, message_ptr(new PongMessage(this->uuid()))));
			break;
		case PONG:
			std::cout << "got pong from " << conn->str() << std::endl;
			break;
		case USER_INFO:
			// Read username, create new user object and add to users. if a connection already exist for user, add to pool? overwrite?

			break;
		case FILE_REQUEST:
			// check if we have file, start sending file on existing/new sokcet?
			// call send_file on user associated with this connection?
			break;
		case FILE_RESPONSE:
			break;
		case FILE_DATA:
			break;
		}
	}

	void Router::register_connection(connection_ptr con)
	{
		boost::mutex::scoped_lock lk(m_connections_mutex);
		std::vector<connection_ptr>::iterator it;
		for (it = m_connections.begin(); it < m_connections.end(); ++it)
		{
			if (*it == con)
			{
				// already registered, wtf?
				std::cout << "ERROR connection already registered!" << std::endl;
				assert(false);
				return;
			}
		}
		this->m_callbacks->OnConnect(con->str());
		m_connections.push_back(con);
	}

	void Router::unregister_connection(connection_ptr con) {
		boost::mutex::scoped_lock lk(m_connections_mutex);
		std::vector<connection_ptr>::iterator it;
		for (it = m_connections.begin(); it < m_connections.end(); ++it)
		{
			if (*it == con)
			{
				m_connections.erase(it);
				//cout << "Router::unregistered " << conn->str() << endl;
			}
		}
	}

	std::string make_daytime_string()
	{
		using namespace std; // For time_t, time and ctime;
		time_t now = time(0);
		return ctime(&now);
	}
	// Send ping packet to all
	void Router::ping() {
		message_ptr ping = message_ptr(new PingMessage(this->uuid()));
		//todo: send to all sockets.
		send_all(ping);
	}
	void Router::send_all(message_ptr msgp)
	{
		std::cout << "sending ping to " << m_connections.size() << " hosts." << std::endl;
		boost::mutex::scoped_lock lk(m_connections_mutex);
		BOOST_FOREACH(connection_ptr conn, m_connections)
		{
			//cout << "Sending " << msgp->str() << " to " << conn->str() << endl;
			conn->do_write(msgp);
			//this->m_io->post(boost::bind(&Connection::do_write, conn, msgp));
		}
	}
	void Router::close()
	{
		this->m_io->stop();
	}

}
