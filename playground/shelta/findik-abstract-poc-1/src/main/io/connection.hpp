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

#include "log.hpp"

#include "protocol.hpp"
#include "abstract_data.hpp"

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

			/*!
			Start processing connection.
			After constructor has been called connection instance will wait till this 
			method has been called. After this method called connection will register 
			itself into services and start processing. 
			*/
			void start_processing();

			/*!
			Protocol of this connection.
			\returns protocol of this connection.
			*/
			enum protocol proto();

			/*!
			Pointer to recieved (remote or local) new data.
			\returns currently proccessed data.
			*/
			abstract_data_ptr current_data();

			/*!
			Socket for the local connection.
			\returns local socket
			*/
			boost::asio::ip::tcp::socket & local_socket();

			/*!
			Remote hostname.
			\returns remote hostname to connect.
			*/
			std::string & remote_hostname();

			/*!
			Remote port.
			\returns remote port to connect.
			*/
			unsigned int & remote_port();

			/*!
			Whether connection is keep alive.
			\returns whether connection is keepalive supported.
			*/
			bool & is_keepalive();

		protected:
			/*!
			Debug logger for server class.
			*/
                        static log4cxx::LoggerPtr debug_logger;

			/*!
			Protocol of this connection.
			*/
			protocol proto_;

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
			void handle_read_local(const boost::system::error_code& err,
				std::size_t bytes_transferred);

			/*!
			Handle completion of a remote write operation.
			
			\param e error code if there is an error
			*/
			void handle_write_remote(const boost::system::error_code& err);

			/*!
			Handle completion of a remote write operation.

			\param err error code if there is an error
			\param bytes_transferred number of transferred bytes
			*/
			void handle_read_remote(const boost::system::error_code& err,
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

			/*!
			Prepare socket for operation. 
			This methods set some socket options: NIO, TCP_NO_DELAY, NO_LINGER.
			\param socket ASIO socket to set options.
			*/
			void prepare_socket(boost::asio::ip::tcp::socket & socket);

			/*!
			Local read buffer.
			*/
			boost::array<char, 8*1024> local_buffer_;

			/*!
			Remote read buffer.
			*/
			boost::array<char, 32*1024> remote_buffer_;

			/*!
			Register to ASIO service to read from local socket.
			*/
			void register_for_local_read();

			/*!
			Register to ASIO service to resolve a hostname.
			\param hostname hostname to resolve.
			*/
			void register_for_resolve(const std::string & hostname, unsigned int port);

			/*!
			Remote hostname.
			*/
			std::string remote_hostname_;

			/*!
			Remote port.
			*/
			unsigned int remote_port_;

			/*!
			Register to ASIO service to write to local socket.
			\param data data to write.
			*/
			void register_for_local_write(boost::asio::const_buffer data);

			/*!
			Register to ASIO service to connect an endpoint.
			\param endpoint endpoint to connect.
			*/
			void register_for_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

			/*!
			Register to ASIO service to write to remote socket.
			\param data data to write.
			*/
			void register_for_remote_write(boost::asio::const_buffer data);

			/*!
			Register to ASIO service to read from remote socket.
			*/
			void register_for_remote_read();

			/*!
			Whether connection is keep alive.
			*/
			bool is_keepalive_;

			/*!
			Shutdown TCP socket.  
			\param socket to shutdown.
			*/
			void shutdown_socket(boost::asio::ip::tcp::socket & socket);

		};
		
		typedef boost::shared_ptr<connection> connection_ptr;
	}
}

#endif

