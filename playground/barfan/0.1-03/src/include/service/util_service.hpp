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

#ifndef FINDIK_SERVICE_UTIL_SERVICE_HPP
#define FINDIK_SERVICE_UTIL_SERVICE_HPP

#include <boost/noncopyable.hpp>

#include "pcre_service.hpp"

namespace findik
{
	namespace service
	{
		/*!
		Container to manage various utilities. 
                \extends boost::noncopyable this class has designed to be not copyable.
		*/
		class util_service :
                        private boost::noncopyable
		{
		public:
			/*!
			Default constructor.
			*/
			util_service();

			/*!
			Destructor.
			*/
			~util_service();

			/*!
			Method to access pcre service.
			\returns pcre_service instance.
			*/
			pcre_service & pcre();

			/*!
			Method to initialize utilities.
			*/
			void start();

		protected:

			/*!
			Pcre service instance.
			*/
			pcre_service pcre_srv_;

		};
	}
}

#endif

