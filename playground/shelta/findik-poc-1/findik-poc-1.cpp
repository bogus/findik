// findik-poc-1.cpp : Simple demonstration of boost async server
// 			commented and slighly modified version of 
// 			http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/tutorial/tutdaytime3.html
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string return_message()
{
	return "zumbara\n";
}

// define class with a shared_pointer context
class tcp_connection 
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	// factory method
	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new tcp_connection(io_service));
	}

	tcp::socket & socket()
	{
		return socket_;
	}

	void start()
	{
		// get message 
		message_ = return_message();

		// register new data (buffer(message)) for write operation to socket_,
		// and after write operation completed, call handle_write method of
		// this object (access with a shared pointer) with arguments
		// error and bytes_transferred
		boost::asio::async_write(socket_, boost::asio::buffer(message_),
			boost::bind(& tcp_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}


private:
	// get a socket instance for io_service
	tcp_connection(boost::asio::io_service & io_service)
		: socket_(io_service)
	{
	}

	void handle_write(const boost::system::error_code&, size_t)
	{
	}

	tcp::socket socket_;
	std::string message_;
};

class tcp_server
{
public:
	// create acceptor with given io_service and listen 0.0.0.0:8080
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 8080))
	{
		// server socket accept loop
		start_accept();
	}
private:
	tcp::acceptor acceptor_;

	void start_accept()
	{
		// in for every new connection create an new tcp_connection instance
		// with factory method create of class tcp_connection for  
		// current io_service
		tcp_connection::pointer new_connection =
			tcp_connection::create(acceptor_.io_service());

		// register accept method and instance for the socket
		// of this new connection.
		// after accepting call method handle_accept of this object with
		// arguments new_connection and error.
		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
				boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code & error)
	{
		if (!error)
		{
			// start l7 operations. 
			new_connection->start();
			// after accepting and registering connection to socket 
			// call accept procedure again. 
			start_accept();
		}
	}
};

int main()
{
	
	try {
		// get io_service
	    boost::asio::io_service io_service;
		// create server with io_service
		tcp_server server(io_service);
		io_service.run();
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}


