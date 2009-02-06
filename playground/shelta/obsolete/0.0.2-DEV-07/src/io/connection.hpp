/*
  Copyright (C) 2008 H. Kerem Cevahir (shelta) <findikmail@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef FINDIK_IO_CONNECTION_HPP
#define FINDIK_IO_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "findik_config.hpp"

#include "reply.hpp"
#include "request.hpp"
#include "response.hpp"
#include "request_parser.hpp"
#include "response_parser.hpp"

#include "request_filter.hpp"
#include "response_filter.hpp"



namespace findik {
namespace io {

/*! 
Represents a single connection. Both local connection and remote connection are handled by this class.

@author H. Kerem Cevahir (shelta)
*/
class connection
  : public boost::enable_shared_from_this<connection>,
    private boost::noncopyable
{
public:
  	/*!
	Construct a connection with the given io_service.
	
	\param io_service Boost ASIO object to create IO services
	\param manager database manager object
	*/
	explicit connection(boost::asio::io_service& io_service,
		findik::persistency::dbmanager::pointer & manager);

  	/*!
	Get the socket associated with the local connection.

	\return local socket
	*/
	boost::asio::ip::tcp::socket& l_socket();

	/*! 
	Get the socket associated with the remote connection.

	\return remote socket
	*/
	boost::asio::ip::tcp::socket& r_socket();

	/*!
	Start the first asynchronous operation for the connection.
	*/
	void start();

private:
	/*!
	Handle completion of a request read operation.

	\param e error code if there is an error
	\param bytes_transferred number of transferred bytes
	*/
	void handle_read_request(const boost::system::error_code& e,
		std::size_t bytes_transferred);

	/*!
	Handle completion of a response write operation.
	
	\param e error code if there is an error
	*/
	void handle_write_response(const boost::system::error_code& e);

	/*!
	Handle completion of a hostname resolve operation of.

	\param err error code if there is an error
	\param endpoint_iterator an object to iterate over resolve results.
	*/
	void handle_resolve_remote(const boost::system::error_code& err,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	/*!
	Handle completion of a connect operation to a remote endpoint.

	\param err error code if there is an error
	\param endpoint_iterator an object to iterate over resolve results. This will be used when io subsystem cannot connect to current endpoint.
	*/
	void handle_connect_remote(const boost::system::error_code& err,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	/*!
	Handle completion of a request write operation.

	\param err error code if there is an error
	*/
	void handle_write_request(const boost::system::error_code& err);

	/*!
	Handle completion of a request write operation.

	\param err error code if there is an error
	\param bytes_transferred number of transferred bytes
	*/
	void handle_read_response(const boost::system::error_code& e,
		std::size_t bytes_transferred);

	/*!
	Sets default FINDIK socket options for given socket.

	\param socket target ASIO socket
	*/
	void set_socket_options(boost::asio::ip::tcp::socket & socket);

	/*!
	Strand to ensure the connection's handlers are not called concurrently.
	*/
	boost::asio::io_service::strand strand_;

	/*!
	Resolver to resolve hostnames.
	*/
	boost::asio::ip::tcp::resolver resolver_;

	/*!
	Socket for the local connection.
	*/
	boost::asio::ip::tcp::socket l_socket_;

	/*!
	Socket for the remote connection.
	*/
	boost::asio::ip::tcp::socket r_socket_;

	/*! 
	Buffer for incoming data.
	*/
	boost::array<char, __FC_SOCKET_BUFFER_SIZE> buffer_;

	/*!
	The incoming request.
	*/
	request request_;
	
	/*!
	Buffer to store request for write operation.
	*/
	boost::asio::streambuf request_sbuf_;

	/*!
	The incoming response.
	*/
	response response_;

	/*!
	Buffer to store response for write operation.
	*/
	boost::asio::streambuf response_sbuf_;

	/*!
	The parser for the incoming request.
	*/
	request_parser request_parser_;

	/*!
	The parser for the incoming response.
	*/
	response_parser response_parser_;

	/*!
	Reply object to generate prepared replies for client when needed.
	*/
	reply reply_;

	/*!
	Database manager object
	*/
	findik::persistency::dbmanager::pointer & manager_;

	/*!
	Debug logger
	*/
	static log4cxx::LoggerPtr debug_logger;
};

/*!
Boost shared pointer for connection.
*/
typedef boost::shared_ptr<connection> connection_ptr;

} // namespace server3
} // namespace http

#endif // FINDIK_IO_CONNECTION_HPP
