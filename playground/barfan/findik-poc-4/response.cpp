#include <boost/lexical_cast.hpp>

#include "response.hpp"

namespace findik {
	namespace io {

		response::response(request & request__) : 
			content_length_(0),
			request_(request__)
		{
		}

		unsigned int response::content_length()
		{
			if (content_length_ == 0)
				for (size_t i = 0; i < headers.size(); ++i)
					if (headers[i].name == "Content-Length")
						content_length_ = boost::lexical_cast< unsigned int >(headers[i].value);

			return content_length_;
		}

		bool response::is_chunked()
		{	
			for (size_t i = 0; i < headers.size(); ++i)
				if (headers[i].name == "Transfer-Encoding" &&
					headers[i].value == "chunked")
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

			for (std::size_t i = 0; i < headers.size(); ++i)
				response_stream << headers[i].name << ": "
							<< headers[i].value << "\r\n";

			response_stream << "Connection: close\r\n";
			response_stream << "\r\n";

			if (has_content()) {
				/*
				for (size_t i = 0; i < headers.size(); ++i)
					if (headers[i].name == "Content-Type" && 
						headers[i].value == "text/html; charset=UTF-8")
						printf("%s",content_raw().c_str());
				*/
				response_stream << content_raw();
			}
		}

		void response::push_to_content(char input)
		{
			content_raw_.push_back(input);
		}

		const std::string & response::content_raw()
		{
			return content_raw_;
		}


	} // end of namespace io
} // end of namespace findik

