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

#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>

#include "service_container.hpp"
#include "filter_reason.hpp"
#include "authentication_result.hpp"
#include "reply_service.hpp"

namespace findik
{
	namespace io
	{
                log4cxx::LoggerPtr connection::debug_logger(log4cxx::Logger::getLogger("findik.io.connection"));

		connection::connection( protocol proto ) :
			proto_(proto),
			local_socket_(FI_SERVICES->io_srv()),
			remote_socket_(FI_SERVICES->io_srv()),
			strand_(FI_SERVICES->io_srv()),
			is_keepalive_(boost::indeterminate),
			remote_port_(0),
			remote_hostname_(""),
			is_streaming_(false),
			local_receive_timer_(FI_SERVICES->io_srv()),
			remote_receive_timer_(FI_SERVICES->io_srv()),
			keepalive_timer_(FI_SERVICES->io_srv())
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
			if (socket.is_open())
			{
				socket.cancel();

				boost::system::error_code ignored_ec;
				socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			}
		}

		void connection::register_for_local_read()
		{
			//LOG4CXX_DEBUG(debug_logger, "Registering connection for local read.");

			if (is_keepalive())
			{
				register_for_keepalive_timeout();
			}
			else
			{
				register_for_local_receive_timeout();
			}

			local_socket_.async_read_some(boost::asio::buffer(local_read_buffer_),
				strand_.wrap(
					boost::bind(&connection::handle_read_local, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)));
		}

		void connection::register_for_remote_read()
		{
			//LOG4CXX_DEBUG(debug_logger, "Registering connection for remote read.");

			register_for_remote_receive_timeout();

			remote_socket_.async_read_some(boost::asio::buffer(remote_read_buffer_),
				strand_.wrap(
					boost::bind(&connection::handle_read_remote, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)));
		}

		void connection::register_for_resolve(const std::string & hostname, unsigned int port)
		{
			LOG4CXX_DEBUG(debug_logger, "Registering connection for remote resolve.");
			boost::asio::ip::tcp::resolver::query query_(
                                hostname, boost::lexical_cast<std::string>(port)
                                );

			FI_SERVICES->resolver_srv().async_resolve(query_,
				boost::bind(&connection::handle_resolve_remote, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::iterator));
		}

		void connection::register_for_local_write()
		{
			//LOG4CXX_DEBUG(debug_logger, "Registering connection for local write.");
			boost::asio::async_write(local_socket_, local_write_buffer_,
				strand_.wrap(
					boost::bind(&connection::handle_write_local, shared_from_this(),
					boost::asio::placeholders::error)));
		}

		void connection::register_for_local_write(char * data_, std::size_t size_)
		{
			//LOG4CXX_DEBUG(debug_logger, "Registering connection for local write.");
			boost::asio::async_write(local_socket_, boost::asio::buffer(data_, size_),
				strand_.wrap(
					boost::bind(&connection::handle_write_local, shared_from_this(),
					boost::asio::placeholders::error)));
		}

		void connection::register_for_remote_write()
		{
			//LOG4CXX_DEBUG(debug_logger, "Registering connection for remote write.");
			boost::asio::async_write(remote_socket_, remote_write_buffer_,
				strand_.wrap(
					boost::bind(&connection::handle_write_remote, shared_from_this(),
					boost::asio::placeholders::error)));
		}

		void connection::register_for_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		{
			LOG4CXX_DEBUG(debug_logger, "Registering connection for remote connect.");
			boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
			remote_socket_.async_connect(endpoint,
				strand_.wrap(boost::bind(&connection::handle_connect_remote, shared_from_this(),
					boost::asio::placeholders::error, ++endpoint_iterator)));
		}

		void connection::register_for_keepalive_timeout()
		{
			unsigned int timeout = 60;

			FI_SERVICES->parser_srv().update_keepalive_timeout_of(shared_from_this(), timeout);

			keepalive_timer_.expires_from_now(boost::posix_time::seconds(timeout));
			keepalive_timer_.async_wait(boost::bind(&connection::handle_timeout, shared_from_this(),
					boost::asio::placeholders::error));
		}

		void connection::cancel_keepalive_timeout()
		{
			keepalive_timer_.cancel();
		}

		void connection::register_for_local_receive_timeout()
		{
			local_receive_timer_.expires_from_now(boost::posix_time::seconds(FI_CONFIG.server_local_receive_timeout()));
			local_receive_timer_.async_wait(boost::bind(&connection::handle_timeout, shared_from_this(),
					boost::asio::placeholders::error));
		}

		void connection::cancel_local_receive_timeout()
		{
			local_receive_timer_.cancel();
		}

		void connection::register_for_remote_receive_timeout()
		{
			remote_receive_timer_.expires_from_now(boost::posix_time::seconds(FI_CONFIG.server_remote_receive_timeout()));
			remote_receive_timer_.async_wait(boost::bind(&connection::handle_timeout, shared_from_this(),
					boost::asio::placeholders::error));
		}

		void connection::cancel_remote_receive_timeout()
		{
			remote_receive_timer_.cancel();
		}

		void connection::handle_timeout(const boost::system::error_code& err)
		{
			if (err != boost::asio::error::operation_aborted)
			{
				close();
			}
		}

		void connection::start_processing()
		{
			prepare_socket(local_socket_);
			register_for_local_read();
		}

		void connection::close()
		{
			LOG4CXX_DEBUG(debug_logger, "Closing connection.");
			shutdown_socket(local_socket_);
			shutdown_socket(remote_socket_);
		}

                bool connection::is_keepalive()
		{
		//	if (boost::logic::indeterminate(is_keepalive_))
			FI_SERVICES->parser_srv().update_is_keepalive_of(shared_from_this(), is_keepalive_);

			return is_keepalive_;
		}

		unsigned int connection::remote_port()
		{
			if (remote_port_ == 0)
				FI_SERVICES->parser_srv().update_port_of(shared_from_this(), remote_port_);

			return remote_port_;
		}

		const std::string & connection::remote_hostname()
		{
			if (remote_hostname_ == "")
				FI_SERVICES->parser_srv().update_hostname_of(shared_from_this(), remote_hostname_);

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

		void connection::mark_as_streaming()
		{
			is_streaming_ = true;
		}

		void connection::mark_as_not_streaming()
		{
			is_streaming_ = false;
		}

		bool connection::is_streaming()
		{
			return is_streaming_;
		}

		void connection::update_current_data(abstract_data_ptr data_)
		{
			new_data_ = data_;
		}

		void connection::push_current_data_to_queue()
		{
			data_queue_.push_front(new_data_);
			new_data_.reset( (abstract_data *) 0 );

			if (data_queue_.size() > FI_CONFIG.connection_queue_size())
				data_queue_.pop_back();
		}

		const std::deque<abstract_data_ptr> & connection::data_queue()
		{
			return data_queue_;
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

			if (is_keepalive())
			{
				cancel_keepalive_timeout();
			}
			else
			{
				cancel_local_receive_timeout();
			}

			// parsing data.
			boost::tribool parser_result;
			boost::tie(parser_result, boost::tuples::ignore) = 
				FI_SERVICES->parser_srv().parse(
					shared_from_this(), true,
					local_read_buffer_.data(), local_read_buffer_.data() + bytes_transferred);

			if (parser_result) // successfully parsed
			{
				//LOG4CXX_DEBUG(debug_logger, "Handling local read: data successfully parsed.");

				bool is_authenticated;
				findik::authenticator::authentication_result_ptr authentication_result;
				boost::tie(is_authenticated, authentication_result) =
					FI_SERVICES->authentication_srv().authenticate(shared_from_this());
				
				if (is_authenticated) // authenticated
				{
					// TODO: save creditentials.

					bool filter_result;
					findik::filter::filter_reason_ptr filter_reason;
					boost::tie(filter_result, filter_reason) =
						FI_SERVICES->filter_srv().filter(shared_from_this());
					
					if (filter_result) // not denied
					{
						//LOG4CXX_DEBUG(debug_logger, "Accepted local data.");

						if (is_keepalive())
						{
							current_data()->into_buffer(remote_write_buffer_);
							register_for_remote_write();
						}
						else
						{
							register_for_resolve(remote_hostname(), remote_port());
						}
					}
					else // denied
					{
						LOG4CXX_DEBUG(debug_logger, "Data from local had been rejected.");

						FI_SERVICES->reply_srv().reply(local_write_buffer_,
								proto(), filter_reason);
						register_for_local_write();
					}
				}
				else // not authenticated
				{
					LOG4CXX_DEBUG(debug_logger, "Local connection is not authenticated.");

					FI_SERVICES->reply_srv().reply(local_write_buffer_,
							proto(), authentication_result);
					register_for_local_write();
				}
			}
			else if (!parser_result) // bad request
			{
				LOG4CXX_ERROR(debug_logger, "Handling local read: data can not be parsed.");

				FI_SERVICES->reply_srv().reply(local_write_buffer_,
						proto(), FC_BAD_LOCAL);
				register_for_local_write();
			}
			else // more data required
			{
				register_for_local_read();
			}
		}

		void connection::handle_resolve_remote(const boost::system::error_code& err,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		{
			//LOG4CXX_DEBUG(debug_logger, "Handling remote resolve.");
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
				//LOG4CXX_DEBUG(debug_logger, "Handling remote connect: successfully connected.");
				prepare_socket(remote_socket_);
				current_data()->into_buffer(remote_write_buffer_);
				register_for_remote_write();
			}
			// not connected, but iterator has more elements
			else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) 
			{
				LOG4CXX_DEBUG(debug_logger, "Handling remote connect: trying next endpoint.");
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
			//LOG4CXX_DEBUG(debug_logger, "Handling remote write.");
			//TODO: call logger
			if (err)
				return;

			push_current_data_to_queue();
			register_for_remote_read();
		}

		void connection::handle_read_remote(const boost::system::error_code& err,
			std::size_t bytes_transferred)
		{
			//TODO: call logger
			if (err && err != boost::asio::error::eof)
				return;

			cancel_remote_receive_timeout();

                        boost::tribool parser_result;

			if ( err == boost::asio::error::eof && 
				current_data().get() != 0 &&
				current_data()->is_expecting_eof() )
			{
				parser_result = true;
			}
			else 
			{
				// parsing data.
				boost::tie(parser_result, boost::tuples::ignore) =
					FI_SERVICES->parser_srv().parse(
						shared_from_this(), false,
						remote_read_buffer_.data(), remote_read_buffer_.data() + bytes_transferred);
			}

                        if (parser_result) // successfully parsed
                        {
				//LOG4CXX_DEBUG(debug_logger, "Handling remote read: data successfully parsed.");

				if (!is_keepalive()) {
					LOG4CXX_DEBUG(debug_logger, "Shutting down remote socket.");
					shutdown_socket(remote_socket_);
				}

				if (current_data()->is_stream())
				{
					mark_as_not_streaming(); // if parser had returned true, all response should have been completed. No need for re-read_remote.
					register_for_local_write(remote_read_buffer_.data(), bytes_transferred);
				}
				else
				{
					bool filter_result;
					findik::filter::filter_reason_ptr filter_reason;
	                                boost::tie(filter_result, filter_reason) =
        	                                FI_SERVICES->filter_srv().filter(shared_from_this());

					if (filter_result) // not denied
					{
						//LOG4CXX_DEBUG(debug_logger, "Accepted remote data.");
						current_data()->into_buffer(local_write_buffer_);
						register_for_local_write();
					}
					else // denied
					{
						LOG4CXX_DEBUG(debug_logger, "Data from remote had been rejected.");
						FI_SERVICES->reply_srv().reply(local_write_buffer_,
								proto(), filter_reason);
						register_for_local_write();
					}
				}
                        }
                        else if (!parser_result) // bad response
                        {
				LOG4CXX_ERROR(debug_logger, "Handling remote read: data can not be parsed.");

				if (!is_keepalive())
                                        shutdown_socket(remote_socket_);

				FI_SERVICES->reply_srv().reply(local_write_buffer_,
						proto(), FC_BAD_REMOTE);
				register_for_local_write();
                        }
                        else // more data required
                        {
				if (current_data()->is_stream())
				{
					mark_as_streaming();
					register_for_local_write(remote_read_buffer_.data(), bytes_transferred);
				}
				else
				{
	                                register_for_remote_read();
				}
                        }
		}

		void connection::handle_write_local(const boost::system::error_code& err)
		{
			//LOG4CXX_DEBUG(debug_logger, "Handling local write.");
			//TODO: call logger
			if (err)
				return;

			if (is_streaming())
			{
				register_for_remote_read();
			}
			else if (is_keepalive()) 
			{
				push_current_data_to_queue();
				register_for_local_read();
			} 
			else
			{
				LOG4CXX_DEBUG(debug_logger, "Shutting down local socket.");
				shutdown_socket(local_socket_);
			}
		}
	}
}

