#ifndef FINDIK_IO_CONNECTION_HPP
#define FINDIK_IO_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "reply.hpp"
#include "request.hpp"
#include "response.hpp"
#include "request_parser.hpp"
#include "response_parser.hpp"

namespace findik {
namespace io {

/// Represents a single connection from a client.
class connection
  : public boost::enable_shared_from_this<connection>,
    private boost::noncopyable
{
public:
  /// Construct a connection with the given io_service.
  explicit connection(boost::asio::io_service& io_service);

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

  /// Strand to ensure the connection's handlers are not called concurrently.
  boost::asio::io_service::strand strand_;

  boost::asio::ip::tcp::resolver resolver_;

  /// Socket for the local connection.
  boost::asio::ip::tcp::socket l_socket_;

  /// Socket for the remote connection.
  boost::asio::ip::tcp::socket r_socket_;

  /// Buffer for incoming data.
  boost::array<char, 8192> buffer_;

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
};

typedef boost::shared_ptr<connection> connection_ptr;

} // namespace server3
} // namespace http

#endif // FINDIK_IO_CONNECTION_HPP
