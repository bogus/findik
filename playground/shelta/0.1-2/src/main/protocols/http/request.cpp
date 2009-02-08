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

#include "request.hpp"
#include "service_container.hpp"

#include <boost/foreach.hpp>

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			request::request() :
				request_path_(""),
				request_uri_("")
			{
				content_length_ = 0;
				is_local_ = true;
			}

			request::~request()
			{}

			void request::into_buffer(boost::asio::streambuf & sbuf)
			{
				std::ostream request_stream(&sbuf);

				if (method == get)
					request_stream << "GET";
				else if (method == post)
					request_stream << "POST";
				else if (method == head)
					request_stream << "HEAD";
				else if (method == put)
					request_stream << "PUT";
				else if (method == delete_)
					request_stream << "DELETE";
				else if (method == trace)
					request_stream << "TRACE";
				else if (method == options)
					request_stream << "OPTIONS";
				else if (method == connect)
					request_stream << "CONNECT";

				request_stream	<< " ";

				if (FI_SERVICES->config_srv().returnBool("findik.server.http.run_with_squid"))
				{
					request_stream << request_uri();
				}
				else
				{
					request_stream << request_path();
				}

				request_stream << " HTTP/" << http_version_major << "." << http_version_minor << "\r\n";


				BOOST_FOREACH( header h, get_headers() )
					request_stream << h.name << ": " << h.value << "\r\n";

				request_stream << "\r\n";

				if (has_content())
					request_stream.write(&(content()[0]), content().size());

				clear_content();
			}

			const std::string & request::request_uri()
			{
				if (request_uri_ == "")
					request_path();

				return request_uri_;
			}

			const std::string & request::request_path()
			{
				if (request_path_ == "") 
				{
					if (uri.find("http://") == 0)
					{
						request_uri_ = uri;
						request_path_ = uri.substr( 7 + uri.substr(7).find("/"));
					} 
					else
					{
						BOOST_FOREACH( header h, get_headers() )
							if ( h.name == "Host")
								request_uri_ = "http://" + h.value + uri;
						request_path_ = uri;
					}
				}

				return request_path_;
			}

		}
	}
}

