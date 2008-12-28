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

#include "pooled_dbmanager.hpp"

#ifndef FINDIK_POOLED_DBMANAGER_CPP
#define FINDIK_POOLED_DBMANAGER_CPP

namespace findik
{
	namespace persistency
	{
		template <class T>
		void pooled_dbmanager<T>::prepare_pool()
		{
			for (size_t i = 0; i < pool_size_; ++i)
				pool_.push_back(create_connection_object());

			pool_index_ = 0;
		}

		template <class T>
		typename pooled_dbmanager<T>::dbconnection_ptr pooled_dbmanager<T>::get_dbconnection()
		{
			dbconnection_ptr connection;

			do
			{
				connection = pool_[pool_index_];
				pool_index_++;
				pool_index_ = pool_index_%pool_size_;

				LOG4CXX_DEBUG(debug_logger, "trying to get connection " << pool_index_);
			}
			while (!connection->try_lock());

			LOG4CXX_DEBUG(debug_logger, "got connection " << 	pool_index_ << ". returning.");

			return connection;
		}

		template <class T>
		log4cxx::LoggerPtr pooled_dbmanager<T>::debug_logger(log4cxx::Logger::getLogger("findik.persistency.pooled_dbmanager"));

	}
}

#endif
