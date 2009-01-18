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

#ifndef FINDIK_SERVICE_SESSION_SERVICE_HPP
#define FINDIK_SERVICE_SESSION_SERVICE_HPP

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <deque>

namespace findik
{
	namespace service
	{
		/*!
		Service for attaching connections to sessions.
                \extends boost::noncopyable this class has designed to be not copyable.
                \extends boost::enable_shared_from_this<session_service> to use boost shared pointers.
		*/
		class session_service :
                        private boost::noncopyable,
                        public boost::enable_shared_from_this<session_service>
		{
		public:
			/*!
			Default constructor.
			*/
			session_service();

			/*!
			Destructor.
			*/
			~session_service();

		protected:
			/*!
			Queue to store previous sessions.
			When a new connection established, with a protocol specific method, new connection will be 
			attached to a session.
			*/
			std::deque<findik::io::session_ptr> session_queue_;

		}

		typedef boost::shared_ptr<session_service> session_service_ptr;

	}
}

#endif

