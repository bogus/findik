/*
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

/// Represents a single connection from a client.
class connection
  : public boost::enable_shared_from_this<connection>,
    private boost::noncopyable
{
public:
  /// Construct a connection with the given io_service.
  explicit connection(boost::asio::io_service& io_service,
	  findik::persistency::dbmanager::pointer & manager);

  /// Get the socket associated with the local connection.
  boost::asio::ip::tcp::socket& l_socket();

  /// Get the socket associated with the remote connection.
  boost::asio::ip::tcp::socket& r_socket();

  /// Start the first asynchronous operation for the connection.
  void start();

private:
  /// Handle completion of a read operation.
  void handle_read_request(const boost::system::error_code& e,
      std::size_t bytes_transferred);

  /// Handle completion of a write operation.
  void handle_write_response(const boost::system::error_code& e);

  void handle_resolve_remote(const boost::system::error_code& err,
	  boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

  void handle_connect_remote(const boost::system::error_code& err,
	  boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

  void handle_write_request(const boost::system::error_code& err);

  void handle_read_response(const boost::system::error_code& e,
      std::size_t bytes_transferred);

  void set_socket_options(boost::asio::ip::tcp::socket & socket);

  /// Strand to ensure the connection's handlers are not called concurrently.
  boost::asio::io_service::strand strand_;

  boost::asio::ip::tcp::resolver resolver_;

  /// Socket for the local connection.
  boost::asio::ip::tcp::socket l_socket_;

  /// Socket for the remote connection.
  boost::asio::ip::tcp::socket r_socket_;

  /// Buffer for incoming data.
  boost::array<char, __FC_SOCKET_BUFFER_SIZE> buffer_;

  /// The incoming request.
  request request_;
  boost::asio::streambuf request_sbuf_;

  /// The incoming response.
  response response_;
  boost::asio::streambuf response_sbuf_;

  /// The parser for the incoming request.
  request_parser request_parser_;

  /// The parser for the incoming response.
  response_parser response_parser_;

  /// The reply to be sent back to the client.
  reply reply_;

  /// Database manager object
  findik::persistency::dbmanager::pointer & manager_;

  /// Debug logger
  static log4cxx::LoggerPtr debug_logger;
};

typedef boost::shared_ptr<connection> connection_ptr;

} // namespace server3
} // namespace http

#endif // FINDIK_IO_CONNECTION_HPP
