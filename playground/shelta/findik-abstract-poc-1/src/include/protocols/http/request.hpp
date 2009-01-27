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

#ifndef FINDIK_PROTOCOLS_HTTP_REQUEST_HPP
#define FINDIK_PROTOCOLS_HTTP_REQUEST_HPP

#include <boost/asio.hpp>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "data.hpp"

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			/*!
			Local data implementation for HTTP protocol.
			\extends boost::enable_shared_from_this<abstract_data> to use boost shared pointers.
			\extends findik::protocols::http::data because this is a data for http protocol.
			@author H. Kerem Cevahir (shelta)
			*/
			class request :
				public boost::enable_shared_from_this<request>,
				public findik::protocols::http::data
			{
			public:
				request();
				~request();

				virtual boost::asio::const_buffer to_buffer() = 0;

			protected:
				
			};
			
			typedef boost::shared_ptr<request> request_ptr;
		}
	}
}

#endif

