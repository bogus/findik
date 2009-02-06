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

#ifndef FINDIK_IO_REQUEST_PARSER_HPP
#define FINDIK_IO_REQUEST_PARSER_HPP

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include "request.hpp"

namespace findik {
namespace io {

/*!
Parser for incoming requests.

@author H. Kerem Cevahir (shelta)
*/
class request_parser
{
public:
	/*!
	Construct ready to parse the request method.
	*/
	request_parser();

	/*!
	Reset to initial parser state.
	*/
	void reset();

	/*!
	Parse some data. The tribool return value is true when a complete request
	has been parsed, false if the data is invalid, indeterminate when more
	data is required. The InputIterator return value indicates how much of the
	input has been consumed.

	\param req request object to be populated
	\param begin start point of parser
	\param end stop point of parser

	\return a tuple which contains parse result and begin point. Parse result will be true if input is a proper HTTP request and parsed successfully, false if input is not a proper HTTP request, indeterminate if parser needs more data to decide whether input is proper.
	*/
	template <typename InputIterator>
	boost::tuple<boost::tribool, InputIterator> parse(request& req,
	InputIterator begin, InputIterator end)
	{
		while (begin != end)
		{
			boost::tribool result = consume(req, *begin++);
			if (result || !result)
				return boost::make_tuple(result, begin);
		}

		boost::tribool result = boost::indeterminate;
		return boost::make_tuple(result, begin);
	}

private:
	/*!
	Handle the next character of input.
	
	\param req request object to populate
	\return true if input is a proper HTTP request and parsed successfully, false if input is not a proper HTTP request, indeterminate if parser needs more data to decide whether input is proper.
	*/
	boost::tribool consume(request& req, char input);

	/*!
	The current state of the parser.
	*/
	enum state
	{
		method_start,
		method,
		uri_start,
		uri,
		http_version_h,
		http_version_t_1,
		http_version_t_2,
		http_version_p,
		http_version_slash,
		http_version_major_start,
		http_version_major,
		http_version_minor_start,
		http_version_minor,
		expecting_newline_1,
		header_line_start,
		header_lws,
		header_name,
		space_before_header_value,
		header_value,
		expecting_newline_2,
		expecting_newline_3,
		content
	} state_;

	/*!
	Method of request currently being parsed.
	*/
	std::string method_;

};

} // namespace server3
} // namespace http

#endif // FINDIK_IO_REQUEST_PARSER_HPP
