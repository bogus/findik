#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include "zlib_util.hpp"

#include "response.hpp"

namespace findik {
	namespace io {

		response::response(request & request__) : 
			content_length_(0),
			request_(request__),
			content_encoding_(indeterminate)
		{
		}

		unsigned int response::content_length()
		{
			if (content_length_ == 0)
				BOOST_FOREACH( header h, headers )
					if (h.name == "Content-Length")
						content_length_ = boost::lexical_cast< unsigned int >(h.value);

			return content_length_;
		}

		bool response::is_chunked()
		{	
			BOOST_FOREACH( header h, headers )
				if (h.name == "Transfer-Encoding" && h.value == "chunked")
					return true;
			return false;
		}

		bool response::has_content()
		{
			return get_request().method != 
				findik::io::request::method_type::head;
		}

		request & response::get_request()
		{
			return request_;
		}

		void response::to_streambuf(boost::asio::streambuf &sbuf_)
		{
		std::ostream response_stream(&sbuf_);
		
		response_stream << "HTTP/" << http_version_major << "." 
			<< http_version_minor << " " << status_code << " "
			<< status_line << "\r\n";

		BOOST_FOREACH( header h, headers )
			response_stream << h.name << ": " << h.value << "\r\n";

		response_stream << "Connection: close\r\n";
		response_stream << "\r\n";

		if (has_content())
			response_stream << content_raw();

		//if (content_type().find("text/") != std::string::npos)
		//	std::cout << content();
		}

		void response::push_to_content(char input, bool is_chunked_data)
		{
			content_raw_.push_back(input);
			if (is_chunked() && is_chunked_data)
				content_chunked_.push_back(input);
		}

		const std::string & response::content_raw()
		{
			return content_raw_;
		}

		const std::string & response::content_type()
		{
			if (content_type_.empty())
				BOOST_FOREACH( header h, headers )
					if (h.name == "Content-Type") {
						std::size_t pos_ = h.value.find_first_of(';');
						if (pos_ == std::string::npos) {
							content_type_ = h.value;
							break;
						}
						
						content_type_ = h.value.substr(0,pos_);
						pos_ = h.value.find("charset=");
						
						if (pos_ == std::string::npos)
							break;

						content_charset_ = h.value.substr(pos_ + 8);
					}

			return content_type_;
		}

		const std::string & response::content_charset()
		{
			if (content_charset_.empty())
				content_type();
			return content_charset_;
		}

		response::content_encoding_type response::content_encoding()
		{
			if (content_encoding_ == indeterminate) {
				bool not_found_ = true;
				BOOST_FOREACH( header h, headers )
					if (h.name == "Content-Encoding") {
						if (h.value == "")
							content_encoding_ = none;
						else if (h.value == "gzip")
							content_encoding_ = gzip;
						else if (h.value == "deflate")
							content_encoding_ = deflate;
						else
							content_encoding_ = other;
						not_found_ = false;
						break;
					}
					if (not_found_)
					content_encoding_ = none;
			}

			return content_encoding_;
		}

		const std::string & response::content_data()
		{
			if (is_chunked())
				return content_chunked_;
			else
				return content_raw_;
		}

		const std::string & response::content()
		{
			switch (content_encoding())
			{
			case none:
				return content_data();
			case gzip:
			case deflate:
				if (content_uncompressed_.empty())
					if (zlib_inflate(content_data(), content_uncompressed_) != Z_OK)
						content_uncompressed_.clear();
				return content_uncompressed_;
			default:
				return content_data();
			}
		}
	} // end of namespace io
} // end of namespace findik

