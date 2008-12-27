/*
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

#ifndef FINDIK_POOLED_DBMANAGER_HPP
#define FINDIK_POOLED_DBMANAGER_HPP

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <vector>

#include "dbmanager.hpp"
#include "dbconnection.hpp"

namespace findik {
	namespace persistency
	{
		template <class T>
		class pooled_dbmanager :
			public findik::persistency::dbmanager,
			public boost::enable_shared_from_this< pooled_dbmanager < T > >
		{

		public:

			typedef boost::shared_ptr< pooled_dbmanager < T > > pointer;

			void prepare_pool();

		protected:

			std::size_t pool_size_;

			std::size_t pool_index_;

			typedef boost::shared_ptr< dbconnection < T > > dbconnection_ptr;

			std::vector<dbconnection_ptr> pool_;

			virtual dbconnection_ptr create_connection_object() = 0;

			dbconnection_ptr get_dbconnection();

		};
	}
}
#include "pooled_dbmanager.cpp"
#endif
