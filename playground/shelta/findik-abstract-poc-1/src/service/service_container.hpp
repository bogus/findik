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

#ifndef FINDIK_SERVICE_SERVICE_CONTAINER_HPP
#define FINDIK_SERVICE_SERVICE_CONTAINER_HPP

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace findik
{
	namespace service
	{
		/*!
		Wrapper class for all supplied services. Via this interfaces all component can access to services.
                \extends boost::noncopyable this class has designed to be not copyable.
                \extends boost::enable_shared_from_this<service_container> to use boost shared pointers.
		*/
		class service_container :
                        private boost::noncopyable,
                        public boost::enable_shared_from_this<service_container>
		{
		public:
			/*!
			Default constructor.
			*/
			service_container();

			/*!
			Destructor.
			*/
			~service_container();

		protected:
			/*!
			Session service instance.
			*/
			session_service session_service_;

			/*!
			Parser service instance.
			*/
			parser_service parser_service_;

			/*!
			Filter service instance.
			*/
			filter_service filter_service_;
		}
		
		typedef boost::shared_ptr<service_container> service_container_ptr;
	}
}

#endif

