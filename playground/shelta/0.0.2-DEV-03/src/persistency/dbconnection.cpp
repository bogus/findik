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

#include "dbconnection.hpp"

#ifndef FINDIK_DBCONNECTION_CPP
#define FINDIK_DBCONNECTION_CPP

namespace findik
{
	namespace persistency
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
			std::map<unsigned int, void *>::iterator it;

			for (it = dbc_objects.begin(); it != dbc_objects.end(); it++)
				delete (*it).second;

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
			return lock_;
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

		template <class T>
		void * dbconnection<T>::get_object(unsigned int key)
		{
			return dbc_objects[key];
		}

		template <class T>
		void dbconnection<T>::set_object(unsigned int key, void *object)
		{
			dbc_objects[key] = object;
		}

	}
}

#endif
