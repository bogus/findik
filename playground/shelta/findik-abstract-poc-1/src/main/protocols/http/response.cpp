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

#include "response.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			response::response() :
				content_encoding_(indeterminate)
			{
				content_length_ = 0;
				is_local_ = false;
			}

			response::~response()
			{}

			bool response::is_chunked()
			{
				if ( is_chunked_ == boost::indeterminate )
				{
					BOOST_FOREACH( header h, get_headers() )
						if (h.name == "Transfer-Encoding" && h.value == "chunked")
						{
							is_chunked_ = true;
							return is_chunked_;
						}
					is_chunked_ = false;
				}

				return is_chunked_;
			}

			const std::string & response::content_type()
			{
				if (content_type_.empty())
					BOOST_FOREACH( header h, get_headers() )
						if (h.name == "Content-Type") {
							std::size_t pos_ = h.value.find_first_of(';');
							if (pos_ == std::string::npos) {
								content_type_ = h.value;
								break;
							}

							content_type_ = h.value.substr(0,pos_);
							pos_ = h.value.find("charset=");

							if (pos_ == std::string::npos)
								break;

							content_charset_ = h.value.substr(pos_ + 8);
						}

				return content_type_;
			}

			const std::string & response::content_charset()
			{
				if (content_charset_.empty())
					content_type();
				return content_charset_;
			}

			response::content_encoding_type response::content_encoding()
			{
				if (content_encoding_ == indeterminate) {
					bool not_found_ = true;
					BOOST_FOREACH( header h, get_headers() )
						if (h.name == "Content-Encoding") {
							if (h.value == "")
								content_encoding_ = none;
							else if (h.value == "gzip")
								content_encoding_ = gzip;
							else if (h.value == "deflate")
								content_encoding_ = deflate;
							else
								content_encoding_ = other;
							not_found_ = false;
							break;
						}
						if (not_found_)
						content_encoding_ = none;
				}

				return content_encoding_;
			}

			boost::asio::const_buffer response::to_buffer()
			{
				int i[3];
				return boost::asio::buffer(i);
			}

		}
	}
}

