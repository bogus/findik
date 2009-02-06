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

#include "connection.hpp"
#include "log_initializer.hpp"
#include <vector>
#include <boost/bind.hpp>

namespace findik {
namespace io {

connection::connection(boost::asio::io_service& io_service,
					   findik::persistency::dbmanager::pointer & manager)
  : strand_(io_service),
    l_socket_(io_service),
	r_socket_(io_service),
	resolver_(io_service),
	manager_(manager),
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
	set_socket_options(l_socket_);

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
		filter::request_filter filter(manager_, request_);

		if(!filter.request_chain_filter())
		{
			reply_ = reply::stock_reply(reply::filtered,filter.get_reply_string());

			boost::asio::async_write(l_socket_, reply_.to_buffers(),
				strand_.wrap(
					boost::bind(&connection::handle_write_response, shared_from_this(),
					boost::asio::placeholders::error)));
		}
		else
		{
			boost::asio::ip::tcp::resolver::query query_(
				request_.host(), "http"
				);

			resolver_.async_resolve(query_,
				boost::bind(&connection::handle_resolve_remote, shared_from_this(),
				  boost::asio::placeholders::error,
				  boost::asio::placeholders::iterator));
		}

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
	set_socket_options(r_socket_);

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

		filter::response_filter filter(manager_,response_);
		if(!filter.response_chain_filter())
		{
			reply_ = reply::stock_reply(reply::bad_request);
			boost::asio::async_write(l_socket_, reply_.to_buffers(),
			  strand_.wrap(
				boost::bind(&connection::handle_write_response, shared_from_this(),
				  boost::asio::placeholders::error)));
		}
		else
		{
			response_.to_streambuf(response_sbuf_);
			// The connection was successful. Send the request.
			boost::asio::async_write(l_socket_, response_sbuf_,
			  strand_.wrap(
				boost::bind(&connection::handle_write_response, shared_from_this(),
				  boost::asio::placeholders::error)));
		}
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

void connection::set_socket_options(boost::asio::ip::tcp::socket & socket)
{
	boost::asio::socket_base::non_blocking_io command(true);
	socket.io_control(command);

	boost::asio::ip::tcp::no_delay no_delay_option(true);
	socket.set_option(no_delay_option);

	boost::asio::socket_base::linger linger_option(false, 0);
	socket.set_option(linger_option);

}

	log4cxx::LoggerPtr connection::debug_logger(log4cxx::Logger::getLogger("findik.io.connection"));

} // namespace server3
} // namespace http
