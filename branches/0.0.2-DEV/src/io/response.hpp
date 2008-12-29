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

#ifndef FINDIK_IO_RESPONSE_HPP
#define FINDIK_IO_RESPONSE_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/logic/tribool.hpp>

#include "header.hpp"
#include "request.hpp"

namespace findik {
namespace io {

/*!
A response received from server.
*/
class response
{
public:
	/*!
	Constructor.
	\param request__ request has been sent to get this response
	*/
	response(request & request__);

	/*!
	Status code of response.
	*/
	enum status_type
	{
		// Informational
		continue_ = 100,
		switching_protocols = 101,
		// success
		ok = 200,
		created = 201,
		accepted = 202,
		no_content = 204,
		reset_content = 205,
		partial_content = 206,
		multiple_choices = 300,
		moved_permanently = 301,
		// redirection
		found = 302,
		see_other = 303,
		not_modified = 304,
		use_proxy = 305,
		switch_proxy = 306,
		temporary_redirect = 307,
		// client error
		bad_request = 400,
		unauthorized = 401,
		payment_required = 402,
		forbidden = 403,
		not_found = 404,
		method_not_allowed = 405,
		not_acceptable = 406,
		proxy_authentication_required = 407,
		request_timeout = 408,
		conflicy = 409,
		gone = 410,
		length_required = 411,
		precondition_failed = 412,
		request_entity_too_large = 413,
		request_uri_too_long = 414,
		unsupported_media_type = 415,
		requested_range_not_satifiable = 416,
		expectation_failed = 417,
		// server error
		internal_server_error = 500,
		not_implemented = 501,
		bad_gateway = 502,
		service_unavailable = 503,
		gateway_timeout = 504,
		http_version_not_supported = 505,
		// http extensions
		processing_webdab = 102,
		request_uri_too_long_ext = 122,
		multi_status_webdav = 207,
		i_am_a_teapot = 418,
		unprocessable_entity_webdav = 422,
		locked_webdav = 423,
		failed_dependency_webdav = 424,
		unordered_collection = 425,
		upgrade_required = 426,
		retry_with = 449,
		blocked = 450,
		variant_also_negotiates = 506,
		insufficient_storage_webdav = 507,
		bandwidth_limit_exceeded = 509,
		not_extended = 510
	} status_code;

	/*!
	HTTP status line associated with response status code.
	*/
	std::string status_line;

	/*!
	Content encoding types for response.
	*/
	enum content_encoding_type {
		gzip,
		deflate,
		none,
		other,
		indeterminate
	};

        /*!
        Major number of HTTP Version in HTTP response command line.
        */
        unsigned int http_version_major;

        /*!
        Minor number of HTTP Version in HTTP response command line.
        */
        unsigned int http_version_minor;

        /*!
        Headers of HTTP response.
        */
        std::vector<header> headers;

        /*!
        Gets length of response content. Most of HTTP responses contain data.

        \return length of request content if "Content-Length" key has been found in headers, else 0.
        */
	unsigned int content_length();

	/*!
	Checks if response content is chunked.
	\return true if content is chunked, else false.ç
	*/
	bool is_chunked();

        /*!
        Crafts a byte stream from response. This method is used while sending resonse to local endpoing (HTTP client).

        \param sbuf_ stream buffer to push bytes into.
        */
	void to_streambuf(boost::asio::streambuf & sbuf_);

	/*!
	Checks if response contains data.

	\return true if response contains data, else false.
	*/
	bool has_content();

	/*!
	Gets raw content of response.

        \return raw content.
	*/
	const std::string & content_raw();

	/*!
	Gets usable content of response data. Response data could be chunked and/or compressed. This methods checks those conditions and handles them.

	\return usable content response.
	*/
	const std::string & content();

	/*!
	Gets request object associated with this response.

	\return request object associated with this response.
	*/
	request & get_request();

        /*!
        Pushes character to raw content vector. If content is chunked, pushes character to chunked content vector, too.

        \param input char to be pushed.
	\param is_chunked_data whether byte is in a chunk. Default is true.
        */
	void push_to_content(char input, bool is_chunked_data = true);

	/*!
	Gets content type of response data. 

	\return type of response content if "Content-Type" key has been found in headers, else "".
	*/
	const std::string & content_type();
	
	/*!
	Gets charset of response content. Only applicable for text mimetypes.
	
	\return charset of response content if content_type() is text and "charset" identifier has been specified, else "".
	*/
	const std::string & content_charset();

	/*!
        Gets content encoding of response data.

        \return encoding of response content if "Content-Encoding" key has been found in headers, else indeterminate.
	*/
	content_encoding_type content_encoding();

private:

	/*!
	Uncompressed content data.
	\sa content()
	*/
	std::string content_uncompressed_;

	/*!
	Chunked content data.
	\sa content(), content_data(), push_to_content(char input, bool is_chunked_data = true)
	*/
	std::string content_chunked_;

	/*!
	Raw content data.
	\sa content(), content_data(), push_to_content(char input, bool is_chunked_data = true)
	*/
	std::string content_raw_;

	/*!
	Length of response content.
	\sa content_length()
	*/
	unsigned int content_length_;

	/*!
	Type of response content.
	\sa content_type()
	*/
	std::string content_type_;

	/*!
	Charset of response content.
	\sa content_charset()
	*/
	std::string content_charset_;

	/*!
	Request object associated with this response.
	\sa request()
	*/
	findik::io::request & request_;

	/*!
	Whether repsonse content is chunked.
	\sa is_chunked()
	*/
	boost::tribool is_chunked_;

	/*!
	Encoding of response content.
	\sa content_encoding()
	*/
	content_encoding_type content_encoding_;

	/*!
	Gets content data. Content may be recieved as chunks. This method checks even if response data is chunked and handles it.

	\return content data.
	*/
	const std::string & content_data();

};

} // namespace server3
} // namespace http
#endif

