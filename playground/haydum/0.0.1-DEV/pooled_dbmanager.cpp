#include "pooled_dbmanager.hpp"

#ifndef FINDIK_POOLED_DBMANAGER_CPP
#define FINDIK_POOLED_DBMANAGER_CPP

namespace findik
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
		}
		while (!connection->try_lock());

		return connection;
	}
	
}

#endif