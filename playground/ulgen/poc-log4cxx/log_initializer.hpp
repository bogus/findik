#ifndef LOG_INITIALIZER_HPP
#define LOG_INITIALIZER_HPP

// include log4cxx header files.
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"

namespace findik {
	class log_initializer
	{		
	public:
		//constructer initialize logger
		log_initializer(void);

		//load conf from log4j conf file
		bool load_conf(std::string conf_file);
		
		//reload conf 
		bool reload_conf(void);

		//reset logging globally
		static void reset(void);

		//shutdown logging globally
		static void shutdown(void);
		
		//destructor
		~log_initializer(void);
		
		//global user logger
		static log4cxx::LoggerPtr user_logger;

		//global debug logger
		static log4cxx::LoggerPtr debug_logger;

		//global filter logger
		static log4cxx::LoggerPtr filter_logger;


	private:
		//log4j file name
		std::string conf_file;				 
	};
	
}
#endif //  LOG_INITIALIZER_HPP

