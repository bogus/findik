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

#ifndef FINDIK_IO_REQUEST_HPP
#define FINDIK_IO_REQUEST_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>

#include "header.hpp"

namespace findik {
namespace io {

/*!
A request received from a client.

@author H. Kerem Cevahir (shelta)
*/
class request
{
public:

	/*!
	Default constructor.
	*/
	request();

	/*!
	Method of request.
	*/
	enum method_type {
		get,
		post,
		head,
		put,
		delete_,
		trace,
		options,
		connect
	} method;
	
	/*!
	Uri in HTTP request command line.
	*/
	std::string uri;
	
	/*!
	Major number of HTTP Version in HTTP request command line.
	*/
	unsigned int http_version_major;
	
	/*!
	Minor number of HTTP Version in HTTP request command line.
	*/
	unsigned int http_version_minor;

	/*!
	Headers of HTTP request.
	*/
	std::vector<header> headers;
	
	/*!
	Gets destination host from headers of request.

	\return host if "Host:" key has been found in headers, else "".
	*/
	const std::string & host();

	/*!
	Gets port of destination host from headers of request.

	\return port if "Host:" key has been found in headers, else 80.
	*/
	unsigned int port ();

	/*!
	Gets full uri of request. This methods craft full uri from HTTP request command line and "Host:" header.

	\return full uri of request.
	*/
	const std::string & get_full_uri ();

	/*!
	Gets request path. This methods gets request path from HTTP request command line.

	\return full uri of request.
	*/
	const std::string & get_request_path ();

	/*!
	Gets length of request content. Some HTTP request methods (POST) may contain data.

	\return length of request content if "Content-Length" key has been found in headers, else 0.
	*/
	unsigned int content_length();

	/*!
	Crafts a byte stream from request. This method is used while sending request to remote endpoing (HTTP server).

	\param sbuf_ stream buffer to push bytes into.
	*/
	void to_streambuf(boost::asio::streambuf & sbuf_);

	/*!
	Checks if request method supports data sending.

	\return true if request method supports data sending, else false.
	*/
	bool has_content();

	/*!
	Gets raw content of request.

	\return raw content.
	*/
	const std::string & content_raw();

	/*!
	Pushes character to raw content vector.

	\param input char to be pushed.
	*/
	void push_to_content(char input);


private:

	/*!
	Raw content.
	\sa push_to_content(char input)
	*/
	std::string content_raw_;

	/*!
	Destination host of request.
	\sa host()
	*/
	std::string host_;

	/*!
	Request path.
	\sa get_request_path()
	*/
	std::string request_path_;

	/*!
	Full uri of request.
	\sa get_full_uri()
	*/
	std::string full_uri_;

	/*!
	Port of destination endpoint.
	\sa port()
	*/
	unsigned int port_;

	/*!
	Length of request content.
	\sa content_length()
	*/
	unsigned int content_length_;
};

} // namespace server3
} // namespace http

#endif // FINDIK_IO_REQUEST_HPP
