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

#ifndef FINDIK_DBCONNECTION_HPP
#define FINDIK_DBCONNECTION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <map>
//#include <boost/thread/locks.hpp>
//#include <boost/thread/shared_mutex.hpp>

namespace findik
{
	namespace persistency
	{
		template <class T>
		class dbconnection :
			public boost::enable_shared_from_this< dbconnection< T > >
		{
		public:
			dbconnection(T * connection);
			~dbconnection(void);

			void lock();
			void unlock();
			bool is_locked();
			bool try_lock();

			T * connection();

			typedef boost::shared_ptr< dbconnection < T > > pointer;

			void * get_object(unsigned int key);

			void set_object(unsigned int key, void * object);

		protected:

			T * connection_;

			bool lock_; // TODO: should be reimplemented with mutexes

			std::map<unsigned int, void *> dbc_objects;
		};
	}
}
#include "dbconnection.cpp"
#endif
