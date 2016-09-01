#include "stdafx.h"
#include "Connection.h"
#include "router.h"

namespace Network {

	//void Connection::Write(std::string message)
	//{
	//	boost::asio::async_write(m_socket, boost::asio::buffer(message),
	//		boost::bind(&Connection::handle_write, shared_from_this(),
	//			boost::asio::placeholders::error,
	//			boost::asio::placeholders::bytes_transferred));
	//}



	std::string Connection::str()
	{
		return m_socket.remote_endpoint().address().to_string();
	}

	connection_ptr Connection::create(boost::asio::io_service & io_service, Router * r, ICallbacks * cb)
	{
		return connection_ptr(new Connection(io_service, r, cb));
	}

	tcp::socket & Connection::socket()
	{
		return m_socket;
	}

	/// Start connection back to client
	void Connection::start()
	{
		std::cout << "New connection: " << m_socket.remote_endpoint().address().to_string() << std::endl;
		//Write("Hello");

		async_read();
	}


	void Connection::handle_write(const boost::system::error_code &, size_t)
	{

	}

	void Connection::async_read()
	{
		message_ptr msgptr(new Message());

		// Read header
		boost::asio::async_read(m_socket, boost::asio::buffer((char*)&msgptr->header(), sizeof(message_header)),
			boost::bind(&Connection::handle_read_header, shared_from_this(),
				boost::asio::placeholders::error, msgptr));
	}

	void Connection::async_write(message_ptr msg)
	{
		{
			boost::mutex::scoped_lock lk(m_mutex);
			m_writeq.push_back(msg);
		}

		boost::system::error_code e;
		do_async_write(e, message_ptr());
	}

	// https://github.com/RJ/libf2f/blob/master/src/connection.cpp
	void Connection::do_async_write(const boost::system::error_code& e, message_ptr finished_msg) {
		if (m_shutdown) return;
		if (e) {
			this->m_callbacks->OnError("Connection::do_async_write: " + e.message());
			return;
		}

		if (m_writeq.empty()) {
			return;
		}
		message_ptr msgp = m_writeq.front();
		m_writeq.pop_front();

		boost::asio::async_write(socket(), msgp->to_buffers(),
			boost::bind(&Connection::do_async_write,
				shared_from_this(),
				boost::asio::placeholders::error,
				msgp));
	}
	void Connection::handle_read_header(const boost::system::error_code &e, message_ptr msgptr)
	{
		if (m_shutdown) return;
		if (e) {
			// Lost connection
			std::cerr << "err " << e.value() << " handle_read_header " << e.message() << std::endl;
			this->m_callbacks->OnDisconnect(this->str());
			return;
		}
		log_packet(msgptr);

		// Allocate space for payload
		msgptr->malloc_payload();
		if (msgptr->length() == 0) {
			handle_read_data(e, msgptr);
		}

		// Read payload
		boost::asio::async_read(m_socket, boost::asio::buffer(msgptr->payload(), msgptr->length()),
			boost::bind(&Connection::handle_read_data, shared_from_this(), boost::asio::placeholders::error, msgptr));
	}

	void Connection::handle_read_data(const boost::system::error_code &e, message_ptr msgptr)
	{
		if (m_shutdown) return;
		if (e) {
			std::cerr << "err " << e.value() << " handle_read_data " << e.message() << std::endl;
			return;
		}
		log_packet(msgptr);
		this->m_router->message_received(msgptr, shared_from_this());
		// wait for next message
		this->async_read();
	}

	void Connection::log_packet(message_ptr msgptr)
	{
		//printf("{0}->{1}: {2}", boost::posix_time::second_clock::local_time(), m_socket.remote_endpoint().address().to_string(), msgptr->str());
		std::cout << boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) << " " << m_socket.remote_endpoint().address().to_string() << " -> " << msgptr->str() << std::endl;
	}
}