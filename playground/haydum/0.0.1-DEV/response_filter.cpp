#include "response_filter.hpp"

namespace findik {
	namespace filter {

		response_filter::response_filter(persistency::dbmanager::pointer & manager, io::response & response):
			manager_(manager), response_(response)
		{
			
		}

		response_filter::~response_filter(void)
		{
			filter_report_ = filter_report::pointer(new filter_report());
		}

		bool response_filter::response_chain_filter()
		{
			if(response_content_type_filter() &&
				response_content_filter())
				return true;

			return false;
		}

		std::string response_filter::get_reply()
		{
			return filter_report_->get_reply_result();
		}

		bool response_filter::response_content_filter()
		{
			if(response_.content_type() == "text/html") {
				html_parser_ = parser::tidy_html_parser::pointer(new findik::parser::tidy_html_parser());
				html_parser_->create_doc(response_.content().c_str());
				html_parser_->parse_html();
				html_parser_->clear();
			}

			return true;
		}

		bool response_filter::response_content_type_filter()
		{
			return true;
		}

	}
}
