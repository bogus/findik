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

#ifndef FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP
#define FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP

#include "domain_request_filter.hpp"
#include "url_request_filter.hpp"
#include <map>

namespace findik {
	namespace filter {
		
		typedef abstract_request_filter * (*ClassFactoryReqFn)( persistency::dbmanager::pointer & manager, io::request & request );

/*!
 This class represents a map for abstract_request_filter implementing classes. 
 This map is consist of class IDs as key and construct function pointer as value
 
 @author Burak Oguz
*/
		class request_filter_factory_impl : public std::map<int,ClassFactoryReqFn>
		{
		public:
			/*!
                        Constructor for this class. Empty. 
                        \warning At next versions add extern facility to integrate external implementations.
			*/
			request_filter_factory_impl(void);
		};
		
		/*!
		Iterator type definition for request_filter_factory_impl.
		*/
		typedef request_filter_factory_impl::const_iterator request_filter_factory_iter;

		/*!
               	Holds map info of abstract_request_filter implementing classes
		\return a map containing class IDs as key and construct function pointer as value
                */
		request_filter_factory_impl& request_filter_factory_map();
		
		/*!
		Static instance of the request_filter_factory_impl. Can be manipulated by generate_request_filter_factory_map()
		at findik start up.
		\sa generate_request_filter_factory_map()
		*/
		static request_filter_factory_impl request_filter_factory_map_;

		/*!
                Generates a map of all registered request filters.
                \sa response_filter_factory_map_
                */
		void generate_request_filter_factory_map();

	}
}

#endif

