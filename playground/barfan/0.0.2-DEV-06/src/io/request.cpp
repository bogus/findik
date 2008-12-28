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

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include "request.hpp"

namespace findik {
namespace io {

	request::request() :
		host_(""),
		request_path_(""),
		full_uri_(""),
			content_length_(0),
			port_(0)
	{
	}

	const std::string & request::host()
	{
		BOOST_FOREACH( header h, headers )
			if (h.name == "Host")
				host_ = h.value;
		return host_;
	}

	unsigned int request::content_length()
	{
		if (content_length_ == 0)
			BOOST_FOREACH( header h, headers )
				if (h.name == "Content-Length")
					content_length_ =
					boost::lexical_cast< unsigned int >(h.value);

		return content_length_;
	}

	const std::string & request::get_full_uri()
	{
		if (full_uri_ == "")
			get_request_path();

		return full_uri_;
	}

	const std::string & request::get_request_path()
	{
		if (request_path_ == "") 
		{
			if (uri.find("http://") == 0)
			{
				full_uri_ = uri;
				request_path_ = uri.substr( 7 + uri.substr(7).find("/"));
			} 
			else
			{
				full_uri_ = "http://" + host() + uri;
				request_path_ = uri;
			}
		}

		return request_path_;
	}

	void request::to_streambuf(boost::asio::streambuf &sbuf_)
	{
		std::ostream request_stream(&sbuf_);

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

		request_stream	<< " " << get_request_path() << " HTTP/" <<
		http_version_major << "." << http_version_minor << "\r\n";

		bool conn_close = false;
		BOOST_FOREACH( header h, headers )
			if (h.name == "Connection") 
			{
				request_stream << "Connection: close\r\n";
				conn_close = true;
			}
			else if	( h.name == "Proxy-Connection" ||
					h.name == "Keep-Alive" )
				continue;
			else
				request_stream << h.name << ": " << h.value << "\r\n";

		if (!conn_close)
			request_stream << "Connection: close\r\n";

		request_stream << "\r\n";

		if (has_content())
			request_stream << content_raw();
	}

	bool request::has_content()
	{
		return method == post;
	}

	unsigned int request::port()
	{
		if (port_ == 0 || port_ > 65535) {
			std::size_t pos_ = host().find_first_of(":");

			if (pos_ == std::string::npos)
				port_ = 80;
			else
				port_ =
					boost::lexical_cast< unsigned int >(host().substr(pos_));
		}

		return port_;
	}

	void request::push_to_content(char input)
	{
		content_raw_.push_back(input);
	}


	const std::string & request::content_raw()
	{
		return content_raw_;
	}

} // namespace server3
} // namespace http
