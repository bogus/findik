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

#include "response_parser.hpp"

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include <string>
#include <cctype>

#include "parser_util.hpp"
#include "request.hpp"
#include "service_container.hpp"
#include "protocol.hpp"

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			response_parser::initializer::initializer()
			{
				response_parser_ptr p(new response_parser());

				FI_SERVICES->parser_srv().register_remote_parser(findik::io::http, p);
			}

			response_parser::initializer response_parser::initializer::instance;


			boost::tuple<boost::tribool, char*> response_parser::parse(
					findik::io::connection_ptr connection_,
					char* begin, char* end
				)
			{
				while (begin != end)
				{
					boost::tribool result = consume(connection_, *begin++);
					if (result || !result)
						return boost::make_tuple(result, begin);
				}

				boost::tribool result = boost::indeterminate;
				return boost::make_tuple(result, begin);
			}

			boost::tribool response_parser::consume(findik::io::connection_ptr connection_, char input)
			{
				if (connection_->current_data().get() == 0)
				{
					FI_STATE_OF(connection_) = http_version_start;
					response_ptr p(new response());
					connection_->update_current_data(p);
				}

				response_ptr resp = boost::static_pointer_cast<response>(connection_->current_data());

				switch (FI_STATE_OF(connection_))
				{
					case http_version_start:
						if (input == 'H')
						{
							FI_STATE_OF(connection_) = http_version_t_1;
							return boost::indeterminate;
						}
						else
							return false;
					case http_version_t_1:
						if (input == 'T')
						{
							FI_STATE_OF(connection_) = http_version_t_2;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case http_version_t_2:
						if (input == 'T')
						{
							FI_STATE_OF(connection_) = http_version_p;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case http_version_p:
						if (input == 'P')
						{
							FI_STATE_OF(connection_) = http_version_slash;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case http_version_slash:
						if (input == '/')
						{
							resp->http_version_major = 0;
							resp->http_version_minor = 0;
							FI_STATE_OF(connection_) = http_version_major_start;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case http_version_major_start:
						if (is_digit(input))
						{
							resp->http_version_major = resp->http_version_major * 10 + input - '0';
							FI_STATE_OF(connection_) = http_version_major;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case http_version_major:
						if (input == '.')
						{
							FI_STATE_OF(connection_) = http_version_minor_start;
							return boost::indeterminate;
						}
						else if (is_digit(input))
						{
							resp->http_version_major = resp->http_version_major * 10 + input - '0';
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case http_version_minor_start:
						if (is_digit(input))
						{
							resp->http_version_minor = resp->http_version_minor * 10 + input - '0';
							FI_STATE_OF(connection_) = http_version_minor;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case http_version_minor:
						if (input == ' ')
						{
							FI_STATE_OF(connection_) = status_code_start;
							return boost::indeterminate;
						}
						else if (is_digit(input))
						{
							resp->http_version_minor = resp->http_version_minor * 10 + input - '0';
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case status_code_start:
						if (is_digit(input))
						{
							FI_STATE_OF(connection_) = status_code;
							FI_TMPSTR_OF(connection_).clear();
							FI_TMPSTR_OF(connection_).push_back(input);
							return boost::indeterminate;
						}
						else
							return false;
					case status_code:
						if (input == ' ')
						{
							resp->status_code = (response::status_type) 
								boost::lexical_cast< unsigned int >(FI_TMPSTR_OF(connection_));
							FI_TMPSTR_OF(connection_).clear();
							FI_STATE_OF(connection_) = status_line_start;
							return boost::indeterminate;
						}
						else if (is_digit(input))
						{
							FI_TMPSTR_OF(connection_).push_back(input);
							return boost::indeterminate;
						}
						else
							return false;
					case status_line_start:
						if (isalpha(input))
						{
							FI_STATE_OF(connection_) = status_line;
							resp->status_line.push_back(input);
							return boost::indeterminate;
						}
						else
							return false;
					case status_line:
						if (isalpha(input) || input == ' ')
						{
							resp->status_line.push_back(input);
							return boost::indeterminate;
						}
						else if (input == '\r')
						{
							FI_STATE_OF(connection_) = expecting_newline_1;
							return boost::indeterminate;
						}
						else
							return false;
					case expecting_newline_1:
						if (input == '\n')
						{
							FI_STATE_OF(connection_) = header_line_start;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case header_line_start:
						if (input == '\r')
						{
							FI_STATE_OF(connection_) = expecting_newline_3;
							return boost::indeterminate;
						}
						else if (!resp->get_headers().empty() && (input == ' ' || input == '\t'))
						{
							FI_STATE_OF(connection_) = header_lws;
							return boost::indeterminate;
						}
						else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
						{
							return false;
						}
						else
						{
							resp->add_blank_header();
							resp->last_header().name.push_back(input);
							FI_STATE_OF(connection_) = header_name;
							return boost::indeterminate;
						}
					case header_lws:
						if (input == '\r')
						{
							FI_STATE_OF(connection_) = expecting_newline_2;
							return boost::indeterminate;
						}
						else if (input == ' ' || input == '\t')
						{
							return boost::indeterminate;
						}
						else if (is_ctl(input))
						{
							return false;
						}
						else
						{
							FI_STATE_OF(connection_) = header_value;
							resp->last_header().value.push_back(input);
							return boost::indeterminate;
						}
					case header_name:
						if (input == ':')
						{
							trim_spaces(resp->last_header().name);
							FI_STATE_OF(connection_) = space_before_header_value;
							return boost::indeterminate;
						}
						else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
						{
							return false;
						}
						else
						{
							resp->last_header().name.push_back(input);
							return boost::indeterminate;
						}
					case space_before_header_value:
						if (input == ' ')
						{
							FI_STATE_OF(connection_) = header_value;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case header_value:
						if (input == '\r')
						{
							trim_spaces(resp->last_header().value);
							FI_STATE_OF(connection_) = expecting_newline_2;
							return boost::indeterminate;
						}
						else if (is_ctl(input))
						{
							return false;
						}
						else
						{
							resp->last_header().value.push_back(input);
							return boost::indeterminate;
						}
					case expecting_newline_2:
						if (input == '\n')
						{
							FI_STATE_OF(connection_) = header_line_start;
							return boost::indeterminate;
						}
						else
						{
							return false;
						}
					case expecting_newline_3:
						if (input != '\n')
							return false;
						else if (resp->is_chunked()) 
						{
							FI_STATE_OF(connection_) = chunked_size_start;
							return boost::indeterminate;
						}
						else if (last_request_of(connection_)->method != request::head)
						{
							if (resp->content_length() == 0)
								return true;
							FI_STATE_OF(connection_) = content;

							return boost::indeterminate;
						}
						else
							return true;
					case content:
						resp->push_to_content(input); // not chunked

						if (resp->content_size() < resp->content_length())
							return boost::indeterminate;
						else
							return true;
					case chunked_size_start:
						if (is_hex(input))
						{
							FI_STATE_OF(connection_) = chunked_size;
							FI_TMPSTR_OF(connection_).clear();
							FI_TMPSTR_OF(connection_).push_back(input);
							resp->push_to_content(input); // not chunked
							return boost::indeterminate;
						}
						else
							return false;
					case chunked_size:
						if (is_hex(input))
						{
							FI_TMPSTR_OF(connection_).push_back(input);
							resp->push_to_content(input); // not chunked
							return boost::indeterminate;
						}
						else if (input == 32) // some implementations use paddings (0x20) between CRLF and size
						{
							resp->push_to_content(input); // not chunked
							return boost::indeterminate;
						}
						else if (input == '\r')
						{
							resp->push_to_content(input); // not chunked
							FI_TMPINT_OF(connection_) = 0;
							FI_TMPINT_OF(connection_) =
								hex2int(FI_TMPSTR_OF(connection_));
							FI_TMPSTR_OF(connection_).clear();
							FI_STATE_OF(connection_) = chunked_newline_1;
							return boost::indeterminate;
						} 
						else
							return false;
					case chunked_newline_1:
						if (input == '\n')
						{
							resp->push_to_content(input); // not chunked
							if (FI_TMPINT_OF(connection_) == 0)
								return true;
							FI_STATE_OF(connection_) = chunked_line;
							return boost::indeterminate;
						}
						else
							return false;
					case chunked_line:
						resp->push_to_content(input); // chunked
						FI_TMPINT_OF(connection_)--;
						if (FI_TMPINT_OF(connection_) == 0)
						{
							FI_STATE_OF(connection_) = chunked_newline_2;
						}
						return boost::indeterminate;
					case chunked_newline_2:
						if (input == '\r')
						{
							resp->push_to_content(input); // not chunked
							FI_STATE_OF(connection_) = chunked_newline_3;
							return boost::indeterminate;
						}
						else
							return false;
					case chunked_newline_3:
						if (input == '\n')
						{
							resp->push_to_content(input); // not chunked
							FI_STATE_OF(connection_) = chunked_size_start;
							return boost::indeterminate;
						}
						else
							return false;
					default:
						return false;
				}

			}

			void response_parser::update_is_keepalive_of(findik::io::connection_ptr connection_, boost::tribool & is_keepalive_)
			{
				if (connection_->current_data()->is_local())
					return;

				response_ptr resp = boost::static_pointer_cast<response>(connection_->current_data());

				BOOST_FOREACH( header h, resp->get_headers() )
					if (h.name == "Connection" || h.name == "Proxy-Connection")
						if ((h.value == "keep-alive") ||
							(h.value == "Keep-alive") ||
							(h.value == "Keep-Alive") 
							)
						{
							is_keepalive_ = true;
							return;
						} 
						else if ((h.value == "close") ||
							(h.value == "Close") 
							)
						{
							is_keepalive_ = false;
							return;
						}

				is_keepalive_ = false;
			}

			request_ptr response_parser::last_request_of(findik::io::connection_ptr connection_)
			{
				request_ptr req;
				BOOST_FOREACH(findik::io::abstract_data_ptr data_, connection_->data_queue())
					if (data_->is_local())
					{
						req = boost::static_pointer_cast<request>(data_);
					}

				return req;
			}

			void response_parser::cleanup(findik::io::connection_ptr connection_)
			{
				parser_state_map_.erase(connection_);
				parser_temp_str_map_.erase(connection_);
				parser_temp_int_map_.erase(connection_);
			}

		}
	}
} 

