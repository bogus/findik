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

#ifndef FINDIK_SERVICE_FILTER_SERVICE_HPP
#define FINDIK_SERVICE_FILTER_SERVICE_HPP

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <list>

namespace findik
{
	namespace service
	{
		/*!
		Manageble container for filters. 
                \extends boost::noncopyable this class has designed to be not copyable.
                \extends boost::enable_shared_from_this<filter_service> to use boost shared pointers.
		*/
		class filter_service :
                        private boost::noncopyable,
                        public boost::enable_shared_from_this<filter_service>
		{
		public:
			/*!
			Default constructor.
			*/
			filter_service();

			/*!
			Destructor.
			*/
			~filter_service();

			/*!
			Examines new_data of connection by using filters in filter_list_.
			\param connection_ connection contains new data to be inspected.
			\returns a tuple containing whether content should be filter or not and reason of this decision.
			*/
			boost::tuple<bool, findik::filter::filter_reason> 
				filter(findik::io::connection_ptr connection_);

		protected:
			/*!
			List to store filters in an order. When filter operation has been requested
			filters in this list will be started to be executed in order.
			*/
			std::list<findik::filter::abstract_filter_ptr> filter_list_;

		}

		typedef boost::shared_ptr<filter_service> filter_service_ptr;

	}
}

#endif

