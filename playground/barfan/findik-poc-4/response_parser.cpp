#include <string>
#include <boost/lexical_cast.hpp>

#include "response_parser.hpp"
#include "response.hpp"
#include "parser_util.hpp"

#include <iostream>

namespace findik {
namespace io {

response_parser::response_parser()
  : state_(http_version_start), status_code_(""),
  chunked_line_length_(0), chunked_line_length_str_("")
{
}

void response_parser::reset()
{
  state_ = http_version_start;
  status_code_ = "";
  chunked_line_length_ = 0;
  chunked_line_length_str_ = "";
}

boost::tribool response_parser::consume(response& resp, char input)
{
  switch (state_)
  {
  case http_version_start:
    if (input == 'H')
    {
		state_ = http_version_t_1;
		return boost::indeterminate;
    }
    else
		return false;
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
      resp.http_version_major = 0;
      resp.http_version_minor = 0;
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
      resp.http_version_major = resp.http_version_major * 10 + input - '0';
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
      resp.http_version_major = resp.http_version_major * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_minor_start:
    if (is_digit(input))
    {
      resp.http_version_minor = resp.http_version_minor * 10 + input - '0';
      state_ = http_version_minor;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case http_version_minor:
    if (input == ' ')
    {
      state_ = status_code_start;
      return boost::indeterminate;
    }
    else if (is_digit(input))
    {
      resp.http_version_minor = resp.http_version_minor * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case status_code_start:
	  if (is_digit(input))
	  {
		  state_ = status_code;
		  status_code_.push_back(input);
		  return boost::indeterminate;
	  }
	  else
		  return false;
  case status_code:
	  if (input == ' ')
	  {
		  resp.status_code = (response::status_type) boost::lexical_cast< unsigned int >(status_code_);
		  status_code_ = "";
		  state_ = status_line_start;
		  return boost::indeterminate;
	  }
	  else if (is_digit(input)){
		  status_code_.push_back(input);
		  return boost::indeterminate;
	  }
	  else
		  return false;
  case status_line_start:
	  if (isalpha(input))
	  {
		  state_ = status_line;
		  resp.status_line.push_back(input);
		  return boost::indeterminate;
	  }
	  else
		  return false;
  case status_line:
	  if (isalpha(input) || input == ' ')
	  {
		  resp.status_line.push_back(input);
		  return boost::indeterminate;
	  }
	  else if (input == '\r')
	  {
		  state_ = expecting_newline_1;
		  return boost::indeterminate;
	  }
	  else
		  return false;	  
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
    else if (!resp.headers.empty() && (input == ' ' || input == '\t'))
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
      resp.headers.push_back(header());
      resp.headers.back().name.push_back(input);
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
      resp.headers.back().value.push_back(input);
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
      resp.headers.back().name.push_back(input);
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
      resp.headers.back().value.push_back(input);
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

	if (resp.is_chunked()) {
		state_ = chunked_size_start;
		return boost::indeterminate;
	} 
	else if (resp.has_content()) 
	{
		if (resp.content_length() == 0)
			return true;
		state_ = content;
		
		return boost::indeterminate;
	}
	else
		return true;
  case content:
	  resp.push_to_content(input);
	  if (resp.content_raw().size() < resp.content_length())
		return boost::indeterminate;
	else
		return true;
  case chunked_size_start:
	  if (is_hex(input))
	  {
		  state_ = chunked_size;
		  chunked_line_length_str_.push_back(input);
		  resp.push_to_content(input);
		  return boost::indeterminate;
	  }
	  else
		  return false;
  case chunked_size:
	  if (is_hex(input))
	  {
		  chunked_line_length_str_.push_back(input);
		  resp.push_to_content(input);
		  return boost::indeterminate;
	  }
	  else if (input == 32) // some implementations use paddings (0x20) between CRLF and size
	  {
		  resp.push_to_content(input);
		  return boost::indeterminate;
	  }
	  else if (input == '\r')
	  {
		  resp.push_to_content(input);
		  chunked_line_length_ = 
			  hex2int(chunked_line_length_str_);
		  chunked_line_length_str_ = "";
		  state_ = chunked_newline_1;
		  return boost::indeterminate;
	  } else
		  return false;
  case chunked_newline_1:
	  if (input == '\n')
	  {
		  resp.push_to_content(input);
		  if (chunked_line_length_ == 0)
			  return true;
		  state_ = chunked_line;
		  return boost::indeterminate;
	  } 
	  else
		  return false;
  case chunked_line:
	  resp.push_to_content(input);
	  chunked_line_length_--;
	  if (chunked_line_length_ == 0) 
	  {
		  state_ = chunked_newline_2;
	  }
	  return boost::indeterminate;
  case chunked_newline_2:
	  if (input == '\r')
	  {
		  resp.push_to_content(input);
		  state_ = chunked_newline_3;
		  return boost::indeterminate;
	  }
	  else
		  return false;
  case chunked_newline_3:
	  if (input == '\n')
	  {
		  resp.push_to_content(input);
		  state_ = chunked_size_start;
		  return boost::indeterminate;
	  }
	  else
		  return false;

  default:
    return false;
  }
}

} // namespace server3
} // namespace http
