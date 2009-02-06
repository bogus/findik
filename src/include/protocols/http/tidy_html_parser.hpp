/*
  Copyright (C) 2008 Burak OGUZ (barfan) <findikmail@gmail.com>

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

#ifndef FINDIK_PROTOCOLS_HTTP_TIDY_HTML_PARSER_HPP
#define FINDIK_PROTOCOLS_HTTP_TIDY_HTML_PARSER_HPP

#include "tidyx.hpp"
#include "log.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace findik {
	namespace protocols {
		namespace http {
			/*!
                        Content(HTML) parser HTTP protocol.
                        \extends boost::enable_shared_from_this<data> to use boost shared pointers.
                        @author Burak OGUZ (barfan)
                        */
			class tidy_html_parser :
				public boost::enable_shared_from_this<tidy_html_parser>
			{
				public:
					 /*!
                                        Default constructor.
                                        */
					tidy_html_parser(void);
					~tidy_html_parser(void);
					/*!
	                                Parses the HTML content given  
        	                        \param content HTML content to be parsed.
                	                */
					void parse(std::vector<char> content);
					/*!
                                        Returns parsed clear text content
                                        \return a reference to parsed clear text.
                                        */
					std::string get_clear_text();
				
				protected:
					static log4cxx::LoggerPtr debug_logger;

				private:
					void dumpNode(Tidy::Node *tnod);
					void dumpDoc();

					std::string clear_text;
					Tidy::Document tdoc;
			};
			
			typedef boost::shared_ptr<tidy_html_parser> tidy_html_parser_ptr;
		}
	}
}

#endif

