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

#include "connection.hpp"

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <string>

#include "service_container.hpp"
#include "filter_reason.hpp"
#include "reply_service.hpp"

namespace findik
{
	namespace io
	{
		connection::connection( protocol proto ) :
			proto_(proto),
			local_socket_(FI_SERVICES->io_srv()),
			remote_socket_(FI_SERVICES->io_srv()),
			strand_(FI_SERVICES->io_srv()),
			is_keepalive_(false)
		{}

		connection::~connection()
		{}

		void connection::prepare_socket(boost::asio::ip::tcp::socket & socket)
		{
		        boost::asio::socket_base::non_blocking_io command(true);
			socket.io_control(command);

			boost::asio::ip::tcp::no_delay no_delay_option(true);
			socket.set_option(no_delay_option);

			boost::asio::socket_base::linger linger_option(false, 0);
			socket.set_option(linger_option);
		}

		void connection::shutdown_socket(boost::asio::ip::tcp::socket & socket)
		{
			boost::system::error_code ignored_ec;
			socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
		}

		void connection::register_for_local_read()
		{
			local_socket_.async_read_some(boost::asio::buffer(local_buffer_),
				strand_.wrap(
					boost::bind(&connection::handle_read_local, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)));
		}

		void connection::register_for_remote_read()
		{
			remote_socket_.async_read_some(boost::asio::buffer(remote_buffer_),
				strand_.wrap(
					boost::bind(&connection::handle_read_remote, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)));
		}

		void connection::register_for_resolve(const std::string & hostname, unsigned int port)
		{
			boost::asio::ip::tcp::resolver::query query_(
                                hostname, boost::lexical_cast<std::string>(port)
                                );

			FI_SERVICES->resolver_srv().async_resolve(query_,
				boost::bind(&connection::handle_resolve_remote, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::iterator));
		}

		void connection::register_for_local_write(boost::asio::const_buffer data)
		{
			boost::asio::async_write(local_socket_, boost::asio::buffer(data),
				strand_.wrap(
					boost::bind(&connection::handle_write_local, shared_from_this(),
					boost::asio::placeholders::error)));
		}

		void connection::register_for_remote_write(boost::asio::const_buffer data)
		{
			boost::asio::async_write(remote_socket_, boost::asio::buffer(data),
				strand_.wrap(
					boost::bind(&connection::handle_write_remote, shared_from_this(),
					boost::asio::placeholders::error)));
		}

		void connection::register_for_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		{
			boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
			remote_socket_.async_connect(endpoint,
				strand_.wrap(boost::bind(&connection::handle_connect_remote, shared_from_this(),
					boost::asio::placeholders::error, ++endpoint_iterator)));
		}


		void connection::start_processing()
		{
			prepare_socket(local_socket_);
			register_for_local_read();
		}

                bool & connection::is_keepalive()
		{
			return is_keepalive_;
		}

		unsigned int & connection::remote_port()
		{
			return remote_port_;
		}

		std::string & connection::remote_hostname()
		{
			return remote_hostname_;
		}

		enum protocol connection::proto()
		{
			return proto_;
		}

		abstract_data_ptr connection::current_data()
		{
			return new_data_;
		}

		boost::asio::ip::tcp::socket & connection::local_socket()
		{
			return local_socket_;
		}

		void connection::handle_read_local(const boost::system::error_code& err,
			std::size_t bytes_transferred)
		{
			// TODO: call logger
			if (err)
				return;
			
			// parsing data.
			boost::tribool parser_result;
			boost::tie(parser_result, boost::tuples::ignore) = 
				FI_SERVICES->parser_srv().parse(
					shared_from_this(),
					local_buffer_.data(), local_buffer_.data() + bytes_transferred);
			
			if (parser_result) // successfully parsed
			{
				bool filter_result;
				findik::filter::filter_reason_ptr filter_reason;
				boost::tie(filter_result, filter_reason) =
					FI_SERVICES->filter_srv().filter(shared_from_this());
				
				if (filter_result) // not denied
				{
					register_for_resolve(remote_hostname(), remote_port());
				}
				else // denied
				{
					register_for_local_write(
							FI_SERVICES->reply_srv().reply(
								proto(), filter_reason
						));
				}
			}
			else if (!parser_result) // bad request
			{
				register_for_local_write(
						FI_SERVICES->reply_srv().reply(
							proto(), FC_BAD_LOCAL
					));
			}
			else // more data required
			{
				register_for_local_read();
			}
		}

		void connection::handle_resolve_remote(const boost::system::error_code& err,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		{
			// TODO: call logger
			if (err)
				return;

			register_for_connect(endpoint_iterator);
		}

		void connection::handle_connect_remote(const boost::system::error_code& err,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		{
			if (!err) // connected
			{
				prepare_socket(remote_socket_);
				register_for_remote_write(current_data()->to_buffer());
			}
			// not connected, but iterator has more elements
			else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) 
			{
				remote_socket_.close();
				register_for_connect(endpoint_iterator);
			}
			else // can not connect
			{
				//TODO: call logger
				return;
			}
		}

		void connection::handle_write_remote(const boost::system::error_code& err)
		{
			//TODO: call logger
			if (err)
				return;

			register_for_remote_read();
		}

		void connection::handle_read_remote(const boost::system::error_code& err,
			std::size_t bytes_transferred)
		{
			//TODO: call logger
			if (err)
				return;

                        // parsing data.
                        boost::tribool parser_result;
                        boost::tie(parser_result, boost::tuples::ignore) =
                                FI_SERVICES->parser_srv().parse(
                                        shared_from_this(),
                                        remote_buffer_.data(), remote_buffer_.data() + bytes_transferred);

                        if (parser_result) // successfully parsed
                        {
				if (!is_keepalive())
					shutdown_socket(remote_socket_);

                                bool filter_result;
                                findik::filter::filter_reason_ptr filter_reason;
                                boost::tie(filter_result, filter_reason) =
                                        FI_SERVICES->filter_srv().filter(shared_from_this());

                                if (filter_result) // not denied
                                {
					register_for_local_write(current_data()->to_buffer());
                                }
                                else // denied
                                {
                                        register_for_local_write(
                                                        FI_SERVICES->reply_srv().reply(
                                                                proto(), filter_reason
                                                ));
                                }
                        }
                        else if (!parser_result) // bad response
                        {
				if (!is_keepalive())
                                        shutdown_socket(remote_socket_);

                                register_for_local_write(
                                                FI_SERVICES->reply_srv().reply(
                                                        proto(), FC_BAD_REMOTE
                                        ));
                        }
                        else // more data required
                        {
                                register_for_remote_read();
                        }
		}

		void connection::handle_write_local(const boost::system::error_code& err)
		{
			//TODO: call logger

			if (err)
				return;

			if (!is_keepalive())
				shutdown_socket(local_socket_);
		}
	}
}

