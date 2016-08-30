#pragma once
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/date_time.hpp>
#include "message.h"

namespace Network {
	using boost::asio::ip::tcp;
	class Connection;
	typedef boost::shared_ptr<Connection> connection_ptr;

	class Connection : public boost::enable_shared_from_this<Connection>
	{
	public:
		void async_read();
		void Write(std::string message);
		std::string str();

		static connection_ptr create(boost::asio::io_service& io_service) {
			return connection_ptr(new Connection(io_service));
		}

		tcp::socket& socket();
		void start();

	private:

		Connection(boost::asio::io_service& io_service)
			: m_socket(io_service)
		{

		};


		void handle_write(const boost::system::error_code& /*error*/,
			size_t /*bytes_transferred*/);


		void handle_read_header(const boost::system::error_code &, message_ptr msgptr);
		void handle_read_data(const boost::system::error_code &, message_ptr msgptr);
		void log_packet(message_ptr msgptr);
		tcp::socket m_socket;
		bool m_shutdown;
		//Connection(const Connection& copy){}
                //Connection& operator=(const Connection& assign) {}
	};

}
