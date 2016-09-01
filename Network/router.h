#pragma once
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Connection.h"
#include "typedefs.h"
using boost::asio::ip::tcp;
namespace Network {
	class Router
	{
	public:
		bool open(boost::asio::io_service& io_service, const char* ip, short port);
		void serve(boost::asio::io_service& io_service, unsigned short port, ICallbacks *cb);
		void message_received(message_ptr msgp, connection_ptr conn);
		void ping();
		void send_all(message_ptr msgp);
		void close();
		std::string uuid();

	private:
		void handle_connect(const boost::system::error_code & e, boost::asio::ip::tcp::endpoint & endpoint, connection_ptr conn);
		void handle_disconnect(connection_ptr conn);
		void register_connection(connection_ptr con);
		void unregister_connection(connection_ptr con);
		void handle_accept(connection_ptr new_connection, const boost::system::error_code& error);
		void start_accept();
		boost::uuids::random_generator generator;
		std::vector<connection_ptr> m_connections;
		boost::mutex m_connections_mutex; // protects connections
		tcp::acceptor* m_acceptor;
		ICallbacks* m_callbacks;
	};
}