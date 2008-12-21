#ifndef FINDIK_DBCONNECTION_HPP
#define FINDIK_DBCONNECTION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
//#include <boost/thread/locks.hpp>
//#include <boost/thread/shared_mutex.hpp>

namespace findik 
{
	template <class T>
	class dbconnection :
		public boost::enable_shared_from_this<dbconnection<T>>
	{
	public:
		dbconnection(T * connection);
		~dbconnection(void);

		void lock();
		void unlock();
		bool is_locked();
		bool try_lock();

		T * connection();

		typedef boost::shared_ptr<dbconnection<T>> pointer;

	protected:

		T * connection_;

		bool lock_; // TODO: should be reimplemented with mutexes
	};
}
#include "dbconnection.cpp"
#endif