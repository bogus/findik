#ifndef FINDIK_PARSER_TIDY_HTML_PARSER_HPP
#define FINDIK_PARSER_TIDY_HTML_PARSER_HPP

#include "html_parser.hpp"
#include <tidy.h>
#include <buffio.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace parser {

		class tidy_html_parser :
			public html_parser, public boost::enable_shared_from_this<tidy_html_parser>
		{
		public:
			tidy_html_parser(void);
			~tidy_html_parser(void);

			void create_doc(const char* html_content);
			void parse_html();
			void clear();
			std::string * get_content();

			typedef boost::shared_ptr<tidy_html_parser> pointer;

		private:
			void dumpNode( TidyNode tnod);
			void dumpDoc();

			TidyDoc tdoc;
		};

	}
}

#endif