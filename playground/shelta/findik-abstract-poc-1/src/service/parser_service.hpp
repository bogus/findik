/*
  Copyright (C) 2008 H. Kerem Cevahir (shelta) <findikmail@gmail.com>

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

#ifndef FINDIK_SERVICE_PARSER_SERVICE_HPP
#define FINDIK_SERVICE_PARSER_SERVICE_HPP

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <list>

namespace findik
{
	namespace service
	{
		/*!
		Manageble container for parsers. 
                \extends boost::noncopyable this class has designed to be not copyable.
                \extends boost::enable_shared_from_this<parser_service> to use boost shared pointers.
		*/
		class parser_service :
                        private boost::noncopyable,
                        public boost::enable_shared_from_this<parser_service>
		{
		public:
			/*!
			Default constructor.
			*/
			parser_service();

			/*!
			Destructor.
			*/
			~parser_service();

			/*!
			Parse some data. The tribool return value is true when a complete request
			has been parsed, false if the data is invalid, indeterminate when more
			data is required. The InputIterator return value indicates how much of the
			input has been consumed.

			\param connection_ connection object to populate data onject into with parsing results. 
			\param begin start point of parser
			\param end stop point of parser

			\return a tuple which contains parse result and begin point. Parse result will be true if input is a proper protocol data and parsed successfully, false if input is not a proper protocol data, indeterminate if parser needs more data to decide whether input is proper.
			*/
			template <typename InputIterator>
			boost::tuple<boost::tribool, InputIterator> parse(
					findik::io::connection_ptr connection_,
					InputIterator begin, InputIterator end
				);

		protected:
			/*!
			List to store parsers in an order. When parsing operation has been requested
			parsers in this list will be started to be executed in order.
			*/
			std::list<findik::parser::abstract_parser_ptr> parser_list_;

		}

		typedef boost::shared_ptr<parser_service> parser_service_ptr;

	}
}

#endif

