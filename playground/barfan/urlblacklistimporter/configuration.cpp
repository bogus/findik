#include "configuration.hpp"

namespace findik {
	namespace importer{
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
}
