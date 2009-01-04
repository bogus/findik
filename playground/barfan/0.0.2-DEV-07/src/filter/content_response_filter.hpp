/*
  Copyright (C) 2008 Burak Oguz (barfan) <findikmail@gmail.com>

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

#ifndef FINDIK_FILTER_CONTENT_RESPONSE_FILTER_HPP
#define FINDIK_FILTER_CONTENT_RESPONSE_FILTER_HPP

#include <pcrecpp.h>
#include <map>
#include "abstract_response_filter.hpp"
#include "tidy_html_parser.hpp"
#include "magic_number_parser.hpp"

namespace findik {
	namespace filter {
/*!
 This class represents an implementation for abstract_response_filter

 @author Burak Oguz
*/
		class content_response_filter :
			public abstract_response_filter, public boost::enable_shared_from_this<content_response_filter>
		{
		public:
			~content_response_filter(void);
			/*!
                        Implementing function of  abstract_response_filter::filter(). Gets content of the response and checks it from
                        database.

                        \return true if content does not contains banned expression
                        */
			bool filter();
			/*!
                        This function will be registered to response_filter_factory_impl map to generate instances of this class.

                        \return an instance of content_response_filter
                        */
			static abstract_response_filter *construct(persistency::dbmanager::pointer & manager, io::response & response);
			/*!
                        Unique ID of this class to generate instances from map.
                        */
			enum { ID = 100 } ;

		private:
			/*!
                        Constructor for this class. Calls only super classes constructor.
                        \param manager database manager object to filter searching
                        \param response response object which filtering operation will use
                        */	
			content_response_filter(persistency::dbmanager::pointer & manager, io::response & response);
			parser::tidy_html_parser::pointer html_parser_;

			/*!
                        Virtual function implementation. Generates report data to be
                        shown to user if filter fails

                        \return report reason string
                        */
                        std::string generate_report_data();

			/*!
			Analyzed content map
			*/
			std::map<std::string,int> pcre_text_analyzed_content;

		protected:
			static log4cxx::LoggerPtr debug_logger;

		};
	}
}

#endif

