#ifndef FINDIK_IO_REQUEST_HPP
#define FINDIK_IO_REQUEST_HPP

#include <string>
#include <vector>
#include "header.hpp"

namespace findik {
namespace io {

/// A request received from a client.
class request
{
public:
  request();
  std::string method;
  std::string uri;
  int http_version_major;
  int http_version_minor;
  std::vector<header> headers;

  std::string & host();
private:
  std::string host_;
};

} // namespace server3
} // namespace http

#endif // FINDIK_IO_REQUEST_HPP
