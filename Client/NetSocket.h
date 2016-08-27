#pragma once
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Connection.h"
#include <iostream>
using boost::asio::ip::tcp;

class NetSocket
{
public:

	void Open(boost::asio::io_service& io_service, std:: string ip, std::string port);
	void Serve(boost::asio::io_service& io_service, unsigned short port);
	void ReadAsync();
	void Read();
	//void Listen(int port);
	void Close();



private:
	//boost::asio::io_service io_service;
	void handle_accept(Connection::pointer new_connection, const boost::system::error_code& error);
	void start_accept();
	tcp::acceptor* _acceptor;
};

