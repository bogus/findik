#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>

namespace findik {
namespace io {

connection::connection(boost::asio::io_service& io_service)
  : strand_(io_service),
    l_socket_(io_service),
	r_socket_(io_service),
	resolver_(io_service),
	response_(request_)
{
}

boost::asio::ip::tcp::socket& connection::l_socket()
{
  return l_socket_;
}

boost::asio::ip::tcp::socket& connection::r_socket()
{
  return r_socket_;
}

void connection::start()
{
  l_socket_.async_read_some(boost::asio::buffer(buffer_),
      strand_.wrap(
        boost::bind(&connection::handle_read_request, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)));
}

void connection::handle_read_request(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
  if (!e)
  {
    boost::tribool result;
    boost::tie(result, boost::tuples::ignore) = request_parser_.parse(
        request_, buffer_.data(), buffer_.data() + bytes_transferred);

    if (result)
    {
		boost::asio::ip::tcp::resolver::query query_(
			request_.host(), "http"
			);
		
		resolver_.async_resolve(query_,
			boost::bind(&connection::handle_resolve_remote, shared_from_this(),
			  boost::asio::placeholders::error,
			  boost::asio::placeholders::iterator));
    }
    else if (!result)
    {
      reply_ = reply::stock_reply(reply::bad_request);
      boost::asio::async_write(l_socket_, reply_.to_buffers(),
          strand_.wrap(
            boost::bind(&connection::handle_write_response, shared_from_this(),
              boost::asio::placeholders::error)));
    }
    else
    {
      l_socket_.async_read_some(boost::asio::buffer(buffer_),
          strand_.wrap(
            boost::bind(&connection::handle_read_request, shared_from_this(),
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred)));
    }
  }
}

  void connection::handle_resolve_remote(const boost::system::error_code& err,
	  boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
  {
	if (!err)
	{
	  // Attempt a connection to the first endpoint in the list. Each endpoint
	  // will be tried until we successfully establish a connection.
	  boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
	  r_socket_.async_connect(endpoint,
		  strand_.wrap(boost::bind(&connection::handle_connect_remote, shared_from_this(),
			boost::asio::placeholders::error, ++endpoint_iterator)));
	}
	else
	{
	  std::cout << "Error: " << err.message() << "\n";
	}
  }
	
  void connection::handle_connect_remote(const boost::system::error_code& err,
	  boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
  {
    if (!err)
    {
	  request_.to_streambuf(request_sbuf_);
      // The connection was successful. Send the request.
	  boost::asio::async_write(r_socket_, request_sbuf_,
          strand_.wrap(boost::bind(&connection::handle_write_request, shared_from_this(),
            boost::asio::placeholders::error)));
    }
    else if (endpoint_iterator != 
		boost::asio::ip::tcp::resolver::iterator())
    {
      // The connection failed. Try the next endpoint in the list.
      r_socket_.close();
	  boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
      r_socket_.async_connect(endpoint,
          strand_.wrap(boost::bind(&connection::handle_connect_remote, shared_from_this(),
            boost::asio::placeholders::error, ++endpoint_iterator)));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }

  void connection::handle_write_request(const boost::system::error_code& err)
  {
    if (!err)
    {
      // Read the response.
	  r_socket_.async_read_some(boost::asio::buffer(buffer_),
      strand_.wrap(
        boost::bind(&connection::handle_read_response, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }

void connection::handle_read_response(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
  if (!e)
  {
    boost::tribool result;
    boost::tie(result, boost::tuples::ignore) = response_parser_.parse(
        response_, buffer_.data(), buffer_.data() + bytes_transferred);
    if (result)
    {
		// Initiate graceful connection closure for remote connection.
		boost::system::error_code ignored_ec;
		r_socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);

		response_.to_streambuf(response_sbuf_);
        // The connection was successful. Send the request.
	
		boost::asio::async_write(l_socket_, response_sbuf_,
          strand_.wrap(
            boost::bind(&connection::handle_write_response, shared_from_this(),
              boost::asio::placeholders::error)));
			  
    }
    else if (!result)
    {
      reply_ = reply::stock_reply(reply::bad_request);
      boost::asio::async_write(l_socket_, reply_.to_buffers(),
          strand_.wrap(
            boost::bind(&connection::handle_write_response, shared_from_this(),
              boost::asio::placeholders::error)));
    }
    else
    {
      r_socket_.async_read_some(boost::asio::buffer(buffer_),
          strand_.wrap(
            boost::bind(&connection::handle_read_response, shared_from_this(),
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred)));
    } 
  } else
	  std::cout << "Resp err: " << e.message() << std::endl;
}


void connection::handle_write_response(const boost::system::error_code& e)
{
	if (!e)
  {
    // Initiate graceful connection closure for local connection.
    boost::system::error_code ignored_ec;
    l_socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
  } else
	  std::cout << "Resp write err: " << e.message() << std::endl;

  // No new asynchronous operations are started. This means that all shared_ptr
  // references to the connection object will disappear and the object will be
  // destroyed automatically after this handler returns. The connection class's
  // destructor closes the socket.
}

} // namespace server3
} // namespace http
