#ifndef FINDIK_PARSER_HTML_PARSER_HPP
#define FINDIK_PARSER_HTML_PARSER_HPP

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace parser {
		class html_parser : public boost::enable_shared_from_this<html_parser>
		{
		public:
			
			virtual void create_doc(const char* html_content) = 0;
			virtual void parse_html() = 0;
			virtual std::string * get_content() = 0;

		protected:

			std::string * parsed_content;
		};

	}
}

#endif

