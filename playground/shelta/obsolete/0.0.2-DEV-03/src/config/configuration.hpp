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

#ifndef FINDIK_CONFIG_CONFIGURATION_HPP
#define FINDIK_CONFIG_CONFIGURATION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <libconfig.h++>
#include <iostream>

namespace findik {
	namespace config {

		class configuration :
			public boost::enable_shared_from_this<configuration>
		{
		public:
			configuration(void);
			~configuration(void);

			bool getConfigValue_String(std::string setting_path,std::string & value);
			bool getConfigValue_Int(std::string setting_path,int & value);

			typedef boost::shared_ptr<configuration> pointer;

		private:
			libconfig::Config config_;
		};

		static configuration configuration_;
	}
}

#endif

