#include "dbconnection.hpp"

#ifndef FINDIK_DBCONNECTION_CPP
#define FINDIK_DBCONNECTION_CPP

namespace findik 
{
	template <class T>
	dbconnection<T>::dbconnection(T * connection) :
		lock_(false),
		connection_(connection)
	{
	}

	template <class T>
	dbconnection<T>::~dbconnection(void)
	{
		delete connection_;
	}

	template <class T>
	void dbconnection<T>::lock()
	{
		lock_ = true;
	}

	template <class T>
	void dbconnection<T>::unlock()
	{
		lock_ = false;
	}

	template <class T>
	bool dbconnection<T>::is_locked()
	{
		return _lock;
	}

	template <class T>
	T * dbconnection<T>::connection()
	{
		return connection_;
	}

	template <class T>
	bool dbconnection<T>::try_lock()
	{
		if (lock_ == true)
			return false;
		else
		{
			lock_ = true;
			return true;
		}
	}

}

#endif