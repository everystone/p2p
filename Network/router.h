#pragma once
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "Connection.h"
#include "typedefs.h"
using boost::asio::ip::tcp;
namespace Network {
	class Router
	{
	public:

		bool Open(boost::asio::io_service& io_service, const char* ip, short port);
		void handle_connect(const boost::system::error_code & e, boost::asio::ip::tcp::endpoint & endpoint, connection_ptr conn);
		void handle_disconnect(connection_ptr conn);
		void Serve(boost::asio::io_service& io_service, unsigned short port, ICallbacks *cb);
		void register_connection(connection_ptr con);
		void unregister_connection(connection_ptr con);
		void Close();



		

	private:
		void handle_accept(connection_ptr new_connection, const boost::system::error_code& error);
		void start_accept();
		std::vector<connection_ptr> m_connections;
		boost::mutex m_connections_mutex; // protects connections
		tcp::acceptor* m_acceptor;
		ICallbacks* m_callbacks;
	};

}