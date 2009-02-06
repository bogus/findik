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

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

#include "service_container.hpp"

namespace findik {
	namespace config {

                log4cxx::LoggerPtr configuration::debug_logger(log4cxx::Logger::getLogger("findik.config.configuration"));

		configuration::configuration(void)
		{
			try 
			{
#if defined(_WIN32)
				config_.readFile("c:/findik.cfg");
#else
				config_.readFile("/etc/findik.cfg");
#endif
			} 
			catch(libconfig::FileIOException & e) 
			{
				LOG4CXX_FATAL(debug_logger, "IOException in config file read");
			} 
			catch(libconfig::ParseException & e) 
			{
				LOG4CXX_FATAL(debug_logger, "ParseException in config file read");
			}
		}

		configuration::~configuration(void)
		{
		}

		bool configuration::check()
		{
			if (FI_SERVICES->config_srv().returnBool("findik.server.http.run_with_squid"))
			{
				std::string hostname_;
				std::string port_;
				unsigned int port__;

				getConfigValue_String("findik.server.http.squid_host", hostname_);
				getConfigValue_UInt("findik.server.http.squid_port", port__);
				port_ = boost::lexical_cast<std::string>(port__);

				boost::asio::ip::tcp::resolver::query query(hostname_, port_);
				try {
					boost::asio::ip::tcp::resolver::iterator endpoint_iterator = 
							FI_SERVICES->resolver_srv().resolve(query);

					boost::asio::ip::tcp::socket socket(FI_SERVICES->io_srv());
					boost::system::error_code error = boost::asio::error::host_not_found;
					while (error && endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
					{
						socket.close();
						socket.connect(*endpoint_iterator++, error);
					}
					socket.close();

					if (error)
					{
						LOG4CXX_FATAL(debug_logger, "Can not connect to squid with given parameters.");
						return false;
					}
				}
				catch (std::exception & e )
				{
					LOG4CXX_FATAL(debug_logger, "Can not connect to squid with given parameters.");
					return false;
				}
			}

			return true;
		}

		bool configuration::getConfigValue_String(std::string setting_path, std::string & value)
		{
			return config_.lookupValue(setting_path,value);
		}

		bool configuration::getConfigValue_UInt(std::string setting_path, unsigned int & value)
		{
			return config_.lookupValue(setting_path,value);
		}

		bool configuration::getConfigValue_Int(std::string setting_path, int & value)
		{
			return config_.lookupValue(setting_path,value);
		}

		bool configuration::getConfigValue_Bool(std::string setting_path, bool & value)
		{
			return config_.lookupValue(setting_path,value);
		}

		bool configuration::returnBool(std::string setting_path)
		{
			bool ret = false;
			getConfigValue_Bool(setting_path, ret);
			return ret;
		}

	}
}
