#include "request_handler_.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace findik {
namespace io {

	request_handler::request_handler(boost::asio::io_service & io_service)
  : resolver_(io_service), io_service_(io_service)
{
}

void request_handler::handle_request(request& req, boost::asio::streambuf & response)
{
  // http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/example/http/client/sync_client.cpp

  boost::asio::streambuf request_;
  std::ostream request_stream(&request_);
  request_stream << req.method << " " << req.uri << " HTTP/" <<
	  req.http_version_major << "." << req.http_version_minor << "\r\n";
  for (std::size_t i = 0; i < req.headers.size(); ++i)
	  if (req.headers[i].name == "Connection" ||
		  req.headers[i].name == "Proxy-Connection")
		  continue;
	  else
		  request_stream << req.headers[i].name << ": "
			<< req.headers[i].value << "\r\n";
  request_stream << "Connection: close\r\n";
  request_stream << "\r\n";

  std::string server(req.host());

  boost::asio::ip::tcp::resolver::query query(server, "http");
  boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
	  resolver_.resolve(query);
  boost::asio::ip::tcp::resolver::iterator end;

  boost::asio::ip::tcp::socket socket(io_service_);

  boost::system::error_code error = boost::asio::error::host_not_found;
    while (error && endpoint_iterator != end)
    {
      socket.close();
      socket.connect(*endpoint_iterator++, error);
    }

	if (error)
      throw boost::system::system_error(error);

	boost::asio::write(socket, request_);

    // Read until EOF, writing data to output as we go.
    while (boost::asio::read(socket, response,
		boost::asio::transfer_at_least(1), error)) 
	{
	}

	if (error != boost::asio::error::eof)
      throw boost::system::system_error(error);

	boost::system::error_code ignored_ec;
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);

}

bool request_handler::url_decode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}

} // namespace server3
} // namespace http
