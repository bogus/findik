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

#include "ssl_connection.hpp"
#include "services.hpp"

#include <boost/bind.hpp>

namespace findik
{
	namespace io
	{
                log4cxx::LoggerPtr ssl_connection::debug_logger(log4cxx::Logger::getLogger("findik.io.ssl_connection"));

		ssl_connection::ssl_connection( protocol proto ) :
			connection(proto),
			local_ssl_socket_(FI_SERVICES->io_srv(), FI_SERVICES->local_ssl_context()),
			remote_ssl_socket_(FI_SERVICES->io_srv(), FI_SERVICES->remote_ssl_context())
		{
			is_secure_ = true;
		}

		ssl_connection::~ssl_connection()
		{}

		void ssl_connection::shutdown_local()
		{
			shutdown_socket(local_socket());
/*			local_ssl_socket_.async_shutdown(strand_.wrap(
					boost::bind(&connection::handle_shutdown_local, 
						shared_from_this(),
						boost::asio::placeholders::error)));
*/		}

		void ssl_connection::shutdown_remote()
		{
			shutdown_socket(remote_socket());
/*			remote_ssl_socket_.async_shutdown(strand_.wrap(
					boost::bind(&connection::handle_shutdown_remote,
						shared_from_this(),
						boost::asio::placeholders::error)));
*/		}

		void ssl_connection::register_for_local_read_io()
		{
			local_ssl_socket_.async_read_some(boost::asio::buffer(local_read_buffer_),
				strand_.wrap(
					boost::bind(&connection::handle_read_local,
						shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)));
		}

		void ssl_connection::register_for_remote_read_io()
		{
			remote_ssl_socket_.async_read_some(boost::asio::buffer(remote_read_buffer_),
				strand_.wrap(
					boost::bind(&connection::handle_read_remote, 
						shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)));
		}

		void ssl_connection::register_for_local_write_io()
		{
			boost::asio::async_write(local_ssl_socket_, local_write_buffer_,
				strand_.wrap(
					boost::bind(&connection::handle_write_local,
					shared_from_this(),
					boost::asio::placeholders::error)));
		}

		void ssl_connection::register_for_local_write_io(char * data_, std::size_t size_)
		{
			boost::asio::async_write(local_ssl_socket_, boost::asio::buffer(data_, size_),
				strand_.wrap(
					boost::bind(&connection::handle_write_local,
					shared_from_this(),
					boost::asio::placeholders::error)));
		}

		void ssl_connection::register_for_remote_write_io()
		{
			boost::asio::async_write(remote_ssl_socket_, remote_write_buffer_,
				strand_.wrap(
					boost::bind(&connection::handle_write_remote,
						shared_from_this(),
						boost::asio::placeholders::error)));
		}

		void ssl_connection::start_local()
		{
			local_ssl_socket_.async_handshake(boost::asio::ssl::stream_base::server,
				strand_.wrap(
					boost::bind(&connection::handle_handshake_local,
						shared_from_this(),
						boost::asio::placeholders::error)));
		}

		void ssl_connection::start_remote()
		{
			remote_ssl_socket_.async_handshake(boost::asio::ssl::stream_base::client,
				strand_.wrap(
					boost::bind(&connection::handle_handshake_remote,
						shared_from_this(),
						boost::asio::placeholders::error)));
		}

		boost::asio::ip::tcp::socket::lowest_layer_type & ssl_connection::local_socket()
		{
			return local_ssl_socket_.lowest_layer();
		}

		boost::asio::ip::tcp::socket::lowest_layer_type & ssl_connection::remote_socket()
		{
			return remote_ssl_socket_.lowest_layer();
		}

		void ssl_connection::handle_handshake_local(const boost::system::error_code& err)
		{
			//TODO: call logger
			if (err)
				return;

			register_for_local_read();
		}

		void ssl_connection::handle_handshake_remote(const boost::system::error_code& err)
		{
			//TODO: call logger
			if (err)
				return;

			current_data()->into_buffer(remote_write_buffer_);
			register_for_remote_write();
		}

		void ssl_connection::handle_shutdown_local(const boost::system::error_code& err)
		{
		}

		void ssl_connection::handle_shutdown_remote(const boost::system::error_code& err)
		{
		}

	}
}

