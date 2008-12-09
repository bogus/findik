// filename of this file changed to request_handler_ from request_handler
// because Microsoft Visual Studio 2008 says that request_handler is a reserved word.

#ifndef FINDIK_IO_REQUEST_HANDLER_HPP
#define FINDIK_IO_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "request.hpp"

namespace findik {
namespace io {

struct reply;

/// The common handler for all incoming requests.
class request_handler
  : private boost::noncopyable
{
public:
  /// Construct with a directory containing files to be served.
	explicit request_handler(boost::asio::io_service & io_service);

  /// Handle a request and produce a reply.
  //void handle_request(const request& req, reply& rep);

  void handle_request(request& req, boost::asio::streambuf & response);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  boost::asio::ip::tcp::resolver resolver_;
  boost::asio::io_service & io_service_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

} // namespace server3
} // namespace http

#endif // FINDIK_IO_REQUEST_HANDLER_HPP
