#include "content_response_filter.hpp"

namespace findik {
	namespace filter {

		content_response_filter::content_response_filter(findik::persistency::dbmanager::pointer & manager, findik::io::response & response)
			: findik::filter::abstract_response_filter(manager, response)
		{
		}

		content_response_filter::~content_response_filter(void)
		{
		}

		bool content_response_filter::filter()
		{
			bool isOk = true;
			if(response_.content_type() == "text/html") {
                                html_parser_ = parser::tidy_html_parser::pointer(new findik::parser::tidy_html_parser());
                                html_parser_->create_doc(response_.content().c_str());
                                html_parser_->parse_html();
                                html_parser_->clear();
                        }
			
			if(!isOk) {
                                LOG4CXX_WARN(logging::log_initializer::filter_logger, response_.get_request().host() << " CONTENT BLOCKED");
                                filter_report_->generate_report(filter_report::response_content,response_.get_request().host());
                        }
			return isOk;
		}
		findik::filter::abstract_response_filter *content_response_filter::construct(persistency::dbmanager::pointer & manager, io::response & response)
		{
			return new content_response_filter(manager,response);
		}


	}
}
