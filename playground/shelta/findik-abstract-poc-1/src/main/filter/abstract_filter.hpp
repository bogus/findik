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

#ifndef FINDIK_FILTER_ABSTRACT_FILTER_HPP
#define FINDIK_FILTER_ABSTRACT_FILTER_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace findik
{
	namespace filter
	{
		/*!
		Type for reasons to return.
		*/
		typedef unsigned int filter_reason;

		/*!
		Abstract filter object to inherit in order to implement filters for findik.
		\extends boost::enable_shared_from_this<abstract_filter> to use boost shared pointers.
		\extends findik::service::service_chain_element to be used in service chains.
		@author H. Kerem Cevahir (shelta)
		*/
		class abstract_filter :
			public boost::enable_shared_from_this<abstract_filter>,
			public findik::service::service_chain_element
		{
		public:
                        /*!
                        Examines new_data of connection by using filters in filter_list_.
			If method returns true for decision, service will execute other filters too,
			otherwise it will stop execution and return false with reason of this operation.
                        \param connection_ connection contains new data to be inspected.
                        \returns a tuple containing whether content should be filter or not and reason of this decision.
                        */
                        virtual boost::tuple<bool, filter_reason> 
				filter(findik::io::connection_ptr connection_) = 0;

		protected:

		}
		
		typedef boost::shared_ptr<abstract_filter> abstract_filter_ptr;
	}
}

#endif

