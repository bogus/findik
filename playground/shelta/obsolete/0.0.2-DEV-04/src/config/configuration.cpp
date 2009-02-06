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

#include "configuration.hpp"

namespace findik {
	namespace config {

		configuration::configuration(void)
		{
			try {
#if defined(_WIN32)
				config_.readFile("c:/findik.cfg");
#else
				config_.readFile("/etc/findik.cfg");
#endif
			} catch(libconfig::FileIOException & e) {
				std::cout << "IOException in config file read" << std::endl;
			} catch(libconfig::ParseException & e) {
				std::cout << "ParseException in config file read" << std::endl;
			}

		}

		configuration::~configuration(void)
		{
		}

		bool configuration::getConfigValue_String(std::string setting_path,std::string & value)
		{
			return config_.lookupValue(setting_path,value);
		}

		bool configuration::getConfigValue_Int(std::string setting_path,int & value)
		{
			return config_.lookupValue(setting_path,value);
		}

	}
}
