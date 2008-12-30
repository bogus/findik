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

#ifndef FINDIK_IO_SERVER_HPP
#define FINDIK_IO_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "connection.hpp"

namespace findik {
namespace io {

/*!
The top-level class of the HTTP server.

@author H. Kerem Cevahir (shelta)
*/
class server
	: private boost::noncopyable
{
public:
	/*!
	Construct the server to listen on the specified TCP address and port, and
	serve up files from the given directory.
	
	\param address local address to listen
	\param port local port to listen
	\param thread_pool_size number of threads. Higher number of threads will provide higher response in return for memory consumption.
	*/
	explicit server(const std::string& address, const std::string& port,
	std::size_t thread_pool_size);

	/*!
	Run the server's io_service loop.
	*/
	void run();

	/*!
	Stop the server.
	*/
	void stop();

private:
	/*!
	Handle completion of an asynchronous accept operation.
	*/
	void handle_accept(const boost::system::error_code& e);

	/*!
	The number of threads that will call io_service::run().
	*/
	std::size_t thread_pool_size_;

	/*!
	The io_service used to perform asynchronous operations.
	*/
	boost::asio::io_service io_service_;

	/*!
	Acceptor used to listen for incoming connections.
	*/
	boost::asio::ip::tcp::acceptor acceptor_;

	/*!
	The next connection to be accepted.
	*/
	connection_ptr new_connection_;

	/*!
	Database manager for database operations.
	*/
	findik::persistency::dbmanager::pointer manager_ptr_;

};

} // namespace server3
} // namespace http

#endif // FINDIK_IO_SERVER_HPP
