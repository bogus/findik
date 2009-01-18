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

#ifndef FINDIK_IO_CONNECTION_HPP
#define FINDIK_IO_CONNECTION_HPP

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/asio.hpp>

#include <deque>

namespace findik
{
	namespace io
	{
		/*!
		Generic connection class for handling data connections and proxying data transmission between them.
		\extends boost::noncopyable because of containing i/o members, copying this class is not safe.
		\extends boost::enable_shared_from_this<connection> to use boost shared pointers.
		@author H. Kerem Cevahir (shelta)
		*/
		class connection :
			private boost::noncopyable,
			public boost::enable_shared_from_this<connection>
		{
		public:
			/*!
			Constructor.
			\param proto protocol of connection.
			*/
			explicit connection( protocol proto );

			/*!
			Destructor.
			*/
			~connection();

		protected:
			/*!
			Protocol of this connection.
			*/
			protocol protocol_;

			/*!
			Socket for the local connection.
			*/
			boost::asio::ip::tcp::socket local_socket_;

			/*!
			Socket for the remote connection.
			*/
			boost::asio::ip::tcp::socket remote_socket_;

			/*!
			Strand to ensure the connection's handlers are not called concurrently.
			*/
			boost::asio::io_service::strand strand_;

			/*!
			Resolver to resolve hostnames.
			*/
			boost::asio::ip::tcp::resolver resolver_;

			/*!
			Handle completion of a hostname resolve operation of.

			\param err error code if there is an error
			\param endpoint_iterator an object to iterate over resolve results.
			*/
			void handle_resolve_remote(const boost::system::error_code& err,
				boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

			/*!
			Handle completion of a connect operation to a remote endpoint.

			\param err error code if there is an error
			\param endpoint_iterator an object to iterate over resolve results. This will be used when io subsystem cannot connect to current endpoint.
			*/
			void handle_connect_remote(const boost::system::error_code& err,
				boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

			/*!
			Handle completion of a local read operation.

			\param e error code if there is an error
			\param bytes_transferred number of transferred bytes
			*/
			void handle_read_local(const boost::system::error_code& e,
				std::size_t bytes_transferred);

			/*!
			Handle completion of a remote write operation.
			
			\param e error code if there is an error
			*/
			void handle_write_remote(const boost::system::error_code& e);

			/*!
			Handle completion of a remote write operation.

			\param err error code if there is an error
			\param bytes_transferred number of transferred bytes
			*/
			void handle_read_remote(const boost::system::error_code& e,
				std::size_t bytes_transferred);

			/*!
			Handle completion of a local write operation.

			\param err error code if there is an error
			*/
			void handle_write_local(const boost::system::error_code& err);

			/*!
			Previously recieved datas. With a max size.
			*/
			std::deque<abstract_data_ptr> data_queue_;

			/*!
			Pointer to recieved (remote or local) new data.
			*/
			abstract_data_ptr new_data_;

		}
		
		typedef boost::shared_ptr<connection> connection_ptr;
	}
}

#endif

