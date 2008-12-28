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

#ifndef FINDIK_FILTER_RESPONSE_FILTER_FACTORY_IMPL_HPP
#define FINDIK_FILTER_RESPONSE_FILTER_FACTORY_IMPL_HPP

#include "content_response_filter.hpp"
#include <map>

namespace findik {
	namespace filter {

		typedef abstract_response_filter * (*ClassFactoryRespFn)( persistency::dbmanager::pointer & manager, io::response & response );
/*!
 This class represents a map for abstract_response_filter implementing classes.
 This map is consist of class IDs as key and construct function pointer as value

 @author Burak Oguz
*/
		class response_filter_factory_impl : public std::map<int,ClassFactoryRespFn>
		{
		public:
			/*!
                        Constructor for this class. Empty.
                        \warning At next versions add extern facility to integrate external implementations.
                        */
			response_filter_factory_impl(void);
		};
		
		/*!
                Iterator type definition for response_filter_factory_impl.
                */
		typedef response_filter_factory_impl::const_iterator response_filter_factory_iter;

		/*!
                Holds map info of abstract_response_filter implementing classes
                \return a map containing class IDs as key and construct function pointer as value
                */
		response_filter_factory_impl& response_filter_factory_map();

		/*!
                Static instance of the response_filter_factory_impl. Can be manipulated by generate_response_filter_factory_map()
                at findik start up.
                \sa generate_response_filter_factory_map()
                */
		static response_filter_factory_impl response_filter_factory_map_;
		
		/*!
		Generates a map of all registered response filters.
		\sa response_filter_factory_map_
		*/
		void generate_response_filter_factory_map();

	}
}

#endif

