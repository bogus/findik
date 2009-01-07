#ifndef FINDIK_IMPORTER_CONFIG_CONFIGURATION_HPP
#define FINDIK_IMPORTER_CONFIG_CONFIGURATION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <libconfig.h++>
#include <iostream>


namespace findik {
	namespace importer {
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
}

#endif
