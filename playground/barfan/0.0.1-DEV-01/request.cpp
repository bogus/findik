#include <boost/lexical_cast.hpp>

#include "request.hpp"

namespace findik {
namespace io {

	request::request() : 
		host_(""), 
			content_length_(0), 
			port_(0)
	{
	}

	std::string & request::host()
	{
		for (std::size_t i = 0; i < headers.size(); ++i)
			if (headers[i].name == "Host")
				host_ = headers[i].value;
		return host_;
	}

	std::string & request::get_uri()
	{
		return uri;
	}

	unsigned int request::content_length()
	{
		if (content_length_ == 0)
			for (size_t i = 0; i < headers.size(); ++i)
				if (headers[i].name == "Content-Length")
					content_length_ = 
					boost::lexical_cast< unsigned int >(headers[i].value);

		return content_length_;
	}

	void request::to_streambuf(boost::asio::streambuf &sbuf_)
	{
		std::ostream request_stream(&sbuf_);
		
		if (method == get)
			request_stream << "GET";
		else if (method == post)
			request_stream << "POST";
		else if (method == head)
			request_stream << "HEAD";
		else if (method == put)
			request_stream << "PUT";
		else if (method == delete_)
			request_stream << "DELETE";
		else if (method == trace)
			request_stream << "TRACE";
		else if (method == options)
			request_stream << "OPTIONS";
		else if (method == connect)
			request_stream << "CONNECT";

		request_stream  << " " << uri << " HTTP/" <<
		http_version_major << "." << http_version_minor << "\r\n";
		for (std::size_t i = 0; i < headers.size(); ++i)
			if (headers[i].name == "Connection" ||
					headers[i].name == "Proxy-Connection" ||
					headers[i].name == "Keep-Alive" )
				continue;
			else
				request_stream << headers[i].name << ": "
						<< headers[i].value << "\r\n";

		request_stream << "Connection: Close\r\n";
		request_stream << "\r\n";

		if (has_content())
			request_stream << content_raw();
	}

	bool request::has_content()
	{
		return method == post;
	}

	unsigned int request::port()
	{
		if (port_ == 0 || port_ > 65535) {
			std::size_t pos_ = host().find_first_of(":");

			if (pos_ == std::string::npos)
				port_ = 80;
			else 
				port_ = 
					boost::lexical_cast< unsigned int >(host().substr(pos_));
		}

		return port_;
	}

	void request::push_to_content(char input)
	{
		content_raw_.push_back(input);
	}


	const std::string & request::content_raw()
	{
		return content_raw_;
	}

} // namespace server3
} // namespace http
