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

#define FI_SERVICES findik::service::service_container::instance()

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/asio.hpp>

#include "session_service.hpp"
#include "filter_service.hpp"
#include "parser_service.hpp"
#include "reply_service.hpp"
#include "configuration.hpp"
#include "mysqldbmanager.hpp"

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
			Destructor.
			*/
			~service_container();

			/*!
			Singleton method.
			\returns singleton instance.
			*/
			static boost::shared_ptr<service_container> instance()
			{
				if (instance_.get() == 0)
					instance_.reset(new service_container());
				return instance_;
			}

			/*!
			Method to start services.
			Some services like db_srv_ needs FI_SERVICES for construction, so we have to create these after initialization.
			*/
			void start();

			/*!
			Boost ASIO IO Service.
			\returns IO Service.
			*/
			boost::asio::io_service & io_srv();

			/*!
			Boost ASIO TCP IP resolver instance.
			\returns TCP/IP resolver.
			*/
			boost::asio::ip::tcp::resolver & resolver_srv();

			/*!
			Session service instance.
			\returns session service instance.
			*/
			session_service & session_srv();

			/*!
			Parser service instance.
			\returns parser service instance.
			*/
			parser_service & parser_srv();

			/*!
			Filter service instance.
			\returns filter service instance.
			*/
			filter_service & filter_srv();

			/*!
			Configuration service instance. To read options from config file.
			\returns config service instance.
			*/
			findik::config::configuration & config_srv();

			/*!
			Reply service instance. To generate replies for local.
			\returns reply service instance.
			*/
			reply_service & reply_srv();

			/*!
			DB Manager to access database via findik specific interface.
			\returns dbmanager instasnce.
			*/
			findik::persistency::mysqldbmanager & db_srv();

		protected:

			/*!
			Singleton instance.
			*/
			static boost::shared_ptr<service_container> instance_;

			/*!
			Default constructor.
			*/
			service_container();

			/*!
			Session service instance.
			*/
			session_service session_srv_;

			/*!
			Parser service instance.
			*/
			parser_service parser_srv_;

			/*!
			Filter service instance.
			*/
			filter_service filter_srv_;

			/*!
			Boost ASIO IO service instance.
			*/
			boost::asio::io_service io_srv_;

			/*!
			Boost ASIO TCP IP resolver instance.
			*/
			boost::asio::ip::tcp::resolver resolver_srv_;

			/*!
			Configuration service instance. To read options from config file.
			*/
			findik::config::configuration config_srv_;

			/*!
			Reply service instance. To generate replies for local.
			*/
			reply_service reply_srv_;

			/*!
			DB Manager to access database via findik specific interface.
			*/
			findik::persistency::mysqldbmanager db_srv_;
		};
		
		typedef boost::shared_ptr<service_container> service_container_ptr;
	}
}

#endif

