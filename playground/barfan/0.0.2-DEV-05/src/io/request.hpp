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

#ifndef FINDIK_IO_REQUEST_HPP
#define FINDIK_IO_REQUEST_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>

#include "header.hpp"

namespace findik {
namespace io {

/// A request received from a client.
class request
{
public:
  request();

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

  std::string uri;
  unsigned int http_version_major;
  unsigned int http_version_minor;
  std::vector<header> headers;



  std::string & host();
  unsigned int port ();

  std::string & get_uri ();
  unsigned int content_length();

  void to_streambuf(boost::asio::streambuf & sbuf_);

  bool has_content();

  const std::string & content_raw();

  void push_to_content(char input);


private:

	std::string content_raw_;

	boost::asio::streambuf content_;

	std::string host_;

	unsigned int port_;

	unsigned int content_length_;
};

} // namespace server3
} // namespace http

#endif // FINDIK_IO_REQUEST_HPP
