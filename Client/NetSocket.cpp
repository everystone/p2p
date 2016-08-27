#include "stdafx.h"
#include "NetSocket.h"
#pragma warning(disable:4996)


void NetSocket::Open(boost::asio::io_service& io_service, std::string ip, std::string port)
{
	try {
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ip, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(io_service);
		//socket.connect(*endpoint_iterator);
		boost::asio::connect(socket, endpoint_iterator);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cin.get();
	}
	std::cout << "Connected to " << ip << ":" << port << std::endl;
}


void NetSocket::handle_accept(Connection::pointer new_connection,
	const boost::system::error_code& error)
{
	if (!error)
	{
		new_connection->start();
	}

	start_accept();
}

void NetSocket::start_accept() {
	Connection::pointer nConnection = Connection::create(this->_acceptor->get_io_service());
	_acceptor->async_accept(nConnection->socket(), boost::bind(&NetSocket::handle_accept, this, nConnection, boost::asio::placeholders::error));
}

void NetSocket::Serve(boost::asio::io_service& io_service, unsigned short port)
{
	this->_acceptor = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port));
}


//
//void NetSocket::Read()
//{
//	try {
//		for (;;) {
//			boost::array<char, 128> buf;
//			boost::system::error_code error;
//			size_t len = this->socket->read_some(boost::asio::buffer(buf), error);
//			
//			if (error == boost::asio::error::eof) {
//				break;
//			}
//			else if (error) {
//				throw boost::system::system_error(error);
//			}
//			std::cout.write(buf.data(), len);
//		}
//	}
//	catch (std::exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//}


std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}
//void NetSocket::Listen(int port)
//{	
//	tcp::acceptor acceptor(this->io_service, tcp::endpoint(tcp::v4(), port));
//	for (;;) {
//		tcp::socket socket(io_service);
//		acceptor.accept(socket);
//		std::string message = make_daytime_string();
//		boost::system::error_code ignored_error;
//		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
//	}
//	std::cout << "Listening on " << port << std::endl;
//}

void NetSocket::Close()
{
}