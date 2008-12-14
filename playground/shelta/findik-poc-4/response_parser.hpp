#ifndef FINDIK_IO_RESPONSE_PARSER_HPP
#define FINDIK_IO_RESPONSE_PARSER_HPP

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include "response.hpp"

namespace findik {
namespace io {

/// Parser for incoming responses.
class response_parser
{
public:
  /// Construct ready to parse the response method.
  response_parser();

  /// Reset to initial parser state.
  void reset();

  /// Parse some data. The tribool return value is true when a complete response
  /// has been parsed, false if the data is invalid, indeterminate when more
  /// data is required. The InputIterator return value indicates how much of the
  /// input has been consumed.
  template <typename InputIterator>
  boost::tuple<boost::tribool, InputIterator> parse(response& resp,
      InputIterator begin, InputIterator end)
  {
    while (begin != end)
    {
      boost::tribool result = consume(resp, *begin++);
      if (result || !result)
        return boost::make_tuple(result, begin);
    }
    boost::tribool result = boost::indeterminate;
    return boost::make_tuple(result, begin);
  }

private:
  /// Handle the next character of input.
  boost::tribool consume(response& resp, char input);

  /// The current state of the parser.
  enum state
  {
    http_version_start,
    http_version_t_1,
    http_version_t_2,
    http_version_p,
    http_version_slash,
    http_version_major_start,
    http_version_major,
    http_version_minor_start,
    http_version_minor,
	status_code_start,
	status_code,
	status_line_start,
	status_line,
    expecting_newline_1,
    header_line_start,
    header_lws,
    header_name,
    space_before_header_value,
    header_value,
    expecting_newline_2,
    expecting_newline_3,
	content,
	chunked_size_start,
	chunked_size,
	chunked_newline_1,
	chunked_line,
	chunked_newline_2,
	chunked_newline_3
  } state_;

  std::string status_code_;

  unsigned int chunked_line_length_;

  std::string chunked_line_length_str_;
};

} // namespace server3
} // namespace http

#endif // FINDIK_IO_RESPONSE_PARSER_HPP
