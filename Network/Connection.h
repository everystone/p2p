#pragma once
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include "message.h"
#include "typedefs.h"


namespace Network {
	using boost::asio::ip::tcp;
	class Connection;
	class Router;
	typedef boost::shared_ptr<Connection> connection_ptr;

	class Connection : public boost::enable_shared_from_this<Connection>
	{
	public:
		void async_read();
		void async_write(message_ptr msg);
		//void Write(std::string message);
		std::string str();

		static connection_ptr create(boost::asio::io_service& io_service, Router* r, ICallbacks* cb);

		tcp::socket& socket();
		void start();

	private:

		Connection(boost::asio::io_service& io_service, Router* router, ICallbacks *cb)
			: m_socket(io_service), m_callbacks(cb), m_router(router)
		{
			//this->m_callbacks = cb;
			//this->m_router = router;
		};


		void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);
		void do_async_write(const boost::system::error_code & e, message_ptr finished_msg);
		void handle_read_header(const boost::system::error_code &, message_ptr msgptr);
		void handle_read_data(const boost::system::error_code &, message_ptr msgptr);
		void log_packet(message_ptr msgptr);
		Router *m_router;
		tcp::socket m_socket;
		bool m_shutdown;
		ICallbacks *m_callbacks;
		boost::mutex m_mutex;
		std::deque<message_ptr> m_writeq;
		//Connection(const Connection& copy){}
				//Connection& operator=(const Connection& assign) {}
	};

}
