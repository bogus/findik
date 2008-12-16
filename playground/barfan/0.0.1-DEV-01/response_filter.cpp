#include "response_filter.hpp"

namespace findik {
	namespace filter {

		response_filter::response_filter(persistency::dbmanager::pointer & manager, io::response & response):
			manager_(manager), response_(response)
		{
		}

		response_filter::~response_filter(void)
		{
		}

		bool response_filter::response_chain_filter()
		{
			if(response_content_type_filter() &&
				response_content_filter())
				return true;

			return false;
		}

		bool response_filter::response_content_filter()
		{
			if(response_.content_type() == "text/html") {
				findik::parser::html_parser *parser = new findik::parser::tidy_html_parser();
				parser->create_doc(response_.content().c_str());
				parser->parse_html();
				delete(parser);
			}

			return true;
		}

		bool response_filter::response_content_type_filter()
		{
			return true;
		}
	}
}
