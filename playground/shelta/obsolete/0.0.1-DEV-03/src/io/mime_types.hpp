#ifndef FINDIK_IO_MIME_TYPES_HPP
#define FINDIK_IO_MIME_TYPES_HPP

#include <string>

namespace findik {
namespace io {
namespace mime_types {

/// Convert a file extension into a MIME type.
std::string extension_to_type(const std::string& extension);

} // namespace mime_types
} // namespace server3
} // namespace http

#endif // FINDIK_IO_MIME_TYPES_HPP
