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

#ifndef FINDIK_PARSER_ABSTRACT_STATEFUL_PARSER_HPP
#define FINDIK_PARSER_ABSTRACT_STATEFUL_PARSER_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <map>

namespace findik
{
	namespace parser
	{

		/*!
		Abstract stateful parser object to inherit in order to implement stateful parsers for findik.
		\extends boost::enable_shared_from_this<abstract_stategul_parser> to use boost shared pointers.
		\extends findik::service::service_chain_element to be used in service chains.
		@author H. Kerem Cevahir (shelta)
		*/
		class abstract_stateful_parser :
			public boost::enable_shared_from_this<abstract_stateful_parser>,
			public findik::parser::abstract_parser
		{
		public:

		protected:
			/*!
			Type for parser states.
			*/
			typedef unsigned int parser_state;
			
			/*!
			A map to store parser states per connection.
			*/
			std::map<findik::io::connection_ptr, parser_state> parser_state_map_;

		};
		
		typedef boost::shared_ptr<abstract_stateful_parser> abstract_stateful_parser_ptr;
	}
}

#endif

