#include "stdafx.h"
#include "Connection.h"


void Connection::Write(std::string message)
{
	boost::asio::async_write(m_socket, boost::asio::buffer(message),
	boost::bind(&Connection::handle_write, shared_from_this(),
	boost::asio::placeholders::error,
	boost::asio::placeholders::bytes_transferred));
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

void Connection::handle_read_header(const boost::system::error_code &e, message_ptr msgptr)
{
	if (m_shutdown) return;
	if (e) {
		std::cerr << "err " << e.value() << " handle_read_header " << e.message() << std::endl;
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


	// wait for next message
	async_read();
}

void Connection::log_packet(message_ptr msgptr)
{
	//printf("{0}->{1}: {2}", boost::posix_time::second_clock::local_time(), m_socket.remote_endpoint().address().to_string(), msgptr->str());
	std::cout << boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) << " " << m_socket.remote_endpoint().address().to_string() << " -> " << msgptr->str() << std::endl;
}

