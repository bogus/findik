#include "request.hpp"

namespace findik {
namespace io {

	request::request() : host_("")
	{
	}

	std::string & request::host()
	{
		if (host_ == "")
			for (std::size_t i = 0; i < headers.size(); ++i)
				if (headers[i].name == "Host")
					host_ = headers[i].value;
		return host_;
	}

} // namespace server3
} // namespace http
