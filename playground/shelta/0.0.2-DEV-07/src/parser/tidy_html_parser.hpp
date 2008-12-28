/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef FINDIK_PARSER_TIDY_HTML_PARSER_HPP
#define FINDIK_PARSER_TIDY_HTML_PARSER_HPP

#include "html_parser.hpp"
#include "tidyx.hpp"
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
			std::string & get_content();

			typedef boost::shared_ptr<tidy_html_parser> pointer;

		private:
			void dumpNode( Tidy::Node *tnod);
			void dumpDoc();

			//TidyDoc tdoc;
			Tidy::Document tdoc;
		};

	}
}

#endif

