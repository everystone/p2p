#include "stdafx.h"
#include "Connection.h"



tcp::socket & Connection::socket()
{
	return _socket;
}

void Connection::start()
{
	_message = "Hello";
	boost::asio::async_write(_socket, boost::asio::buffer(_message), boost::bind(&Connection::handle_write, shared_from_this(),
		boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::handle_write(const boost::system::error_code &, size_t)
{

}
