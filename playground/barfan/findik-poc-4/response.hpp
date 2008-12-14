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

/// A response received from server.
class response
{
public:
  response(request & request__);

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

  std::string status_line;
  unsigned int http_version_major;
  unsigned int http_version_minor;
  std::vector<header> headers;

  unsigned int content_length();

  bool is_chunked();

  void to_streambuf(boost::asio::streambuf & sbuf_);

  bool has_content();

  const std::string & content_raw();

  request & get_request();

  void push_to_content(char input);

private:
  
	std::string content_raw_;

	unsigned int content_length_;

  findik::io::request & request_;

  boost::tribool is_chunked_;
};

} // namespace server3
} // namespace http
#endif