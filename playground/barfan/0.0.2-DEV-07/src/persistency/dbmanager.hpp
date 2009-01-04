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

#ifndef FINDIK_DBMANAGER_HPP
#define FINDIK_DBMANAGER_HPP

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace persistency {
		class dbmanager :
			public boost::enable_shared_from_this<dbmanager>
		{

		public:
			virtual void connectDb() = 0;
			virtual bool domainQuery(std::string hostname) = 0;
			virtual bool urlQuery(std::string url) = 0;
			virtual bool pcreQuery(std::map<int,std::string> &pcre_map) = 0;
			typedef boost::shared_ptr<dbmanager> pointer;

		protected:
			std::string host;
			std::string db;
			std::string username;
			std::string password;
		};
	}
}

#endif
