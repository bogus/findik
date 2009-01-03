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

#ifndef FINDIK_PARSER_HTML_PARSER_HPP
#define FINDIK_PARSER_HTML_PARSER_HPP

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <map>
#include "pcre_parser.hpp"

namespace findik {
	namespace parser {
		class html_parser : public boost::enable_shared_from_this<html_parser>
		{
		public:

			virtual void create_doc(const char* html_content) = 0;
			virtual void parse_html() = 0;
			virtual std::string & get_content() = 0;
			virtual std::map<std::string,int> & get_pcre_text_analyze() = 0;
			
			typedef boost::shared_ptr<html_parser> pointer;

		protected:

			std::string parsed_content;
			std::map<std::string,int> pcre_text_analyzed_content;
		};

	}
}

#endif

