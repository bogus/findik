#include <string>
#include <cctype>

#include "request_parser.hpp"
#include "request.hpp"

#include "parser_util.hpp"

#include <iostream>

namespace findik {
namespace io {

request_parser::request_parser()
  : state_(method_start), method_("")
{
}

void request_parser::reset()
{
  state_ = method_start;
  method_.clear();
}

boost::tribool request_parser::consume(request& req, char input)
{
  switch (state_)
  {
  case method_start:
    if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      state_ = method;
      method_.push_back(toupper(input));
      return boost::indeterminate;
    }
  case method:
    if (input == ' ')
    {
		if (method_ == "GET")
			req.method = findik::io::request::method_type::get;
		else if (method_ == "POST")
			req.method = findik::io::request::method_type::post;
		else if (method_ == "HEAD")
			req.method = findik::io::request::method_type::head;
		else if (method_ == "PUT")
			req.method = findik::io::request::method_type::put;
		else if (method_ == "DELETE")
			req.method = findik::io::request::method_type::delete_;
		else if (method_ == "TRACE")
			req.method = findik::io::request::method_type::trace;
		else if (method_ == "OPTIONS")
			req.method = findik::io::request::method_type::options;
		else if (method_ == "CONNECT")
			req.method = findik::io::request::method_type::connect;
		else 
			return false;
		method_.clear();

      state_ = uri;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      method_.push_back(toupper(input));
      return boost::indeterminate;
    }
  case uri_start:
	  if (is_uri_char(input))
	  {
		  state_ = uri;
		  req.uri.push_back(input);
		  return boost::indeterminate;
	  }
	  else
		  return false;
  case uri:
    if (input == ' ')
    {
      state_ = http_version_h;
      return boost::indeterminate;
    }
	else if (is_uri_char(input))
    {
		req.uri.push_back(input);
        return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_h:
    if (input == 'H')
    {
      state_ = http_version_t_1;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_t_1:
    if (input == 'T')
    {
      state_ = http_version_t_2;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_t_2:
    if (input == 'T')
    {
      state_ = http_version_p;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_p:
    if (input == 'P')
    {
      state_ = http_version_slash;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_slash:
    if (input == '/')
    {
      req.http_version_major = 0;
      req.http_version_minor = 0;
      state_ = http_version_major_start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_major_start:
    if (is_digit(input))
    {
      req.http_version_major = req.http_version_major * 10 + input - '0';
      state_ = http_version_major;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_major:
    if (input == '.')
    {
      state_ = http_version_minor_start;
      return boost::indeterminate;
    }
    else if (is_digit(input))
    {
      req.http_version_major = req.http_version_major * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_minor_start:
    if (is_digit(input))
    {
      req.http_version_minor = req.http_version_minor * 10 + input - '0';
      state_ = http_version_minor;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_minor:
    if (input == '\r')
    {
      state_ = expecting_newline_1;
      return boost::indeterminate;
    }
    else if (is_digit(input))
    {
      req.http_version_minor = req.http_version_minor * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case expecting_newline_1:
    if (input == '\n')
    {
      state_ = header_line_start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case header_line_start:
    if (input == '\r')
    {
      state_ = expecting_newline_3;
      return boost::indeterminate;
    }
    else if (!req.headers.empty() && (input == ' ' || input == '\t'))
    {
      state_ = header_lws;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      req.headers.push_back(header());
      req.headers.back().name.push_back(input);
      state_ = header_name;
      return boost::indeterminate;
    }
  case header_lws:
    if (input == '\r')
    {
      state_ = expecting_newline_2;
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
      state_ = header_value;
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case header_name:
    if (input == ':')
    {
      state_ = space_before_header_value;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      req.headers.back().name.push_back(input);
      return boost::indeterminate;
    }
  case space_before_header_value:
    if (input == ' ')
    {
      state_ = header_value;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case header_value:
    if (input == '\r')
    {
      state_ = expecting_newline_2;
      return boost::indeterminate;
    }
    else if (is_ctl(input))
    {
      return false;
    }
    else
    {
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case expecting_newline_2:
    if (input == '\n')
    {
      state_ = header_line_start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case expecting_newline_3:
	if (input != '\n')
		return false;

	if (req.has_content()) {
		if (req.content_length() == 0)
			return true;

		state_ = content;
		
		return boost::indeterminate;
	}
	else
		return true;
  case content:
	  req.push_to_content(input);
	  if (req.content_raw().size() < req.content_length())
		return boost::indeterminate;
	else
		return true;
  default:
    return false;
  }
}

} // namespace server3
} // namespace http
