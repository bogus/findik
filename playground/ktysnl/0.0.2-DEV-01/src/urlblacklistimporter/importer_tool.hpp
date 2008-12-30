#ifndef FINDIK_IMPORTER_TOOL_IMPORTER_TOOL_HPP
#define FINDIK_IMPORTER_TOOL_IMPORTER_TOOL_HPP

#include <iostream>
#include <string>
#include <boost/filesystem/operations.hpp>
//#include "boost/scoped_ptr.hpp"

namespace findik{
	namespace importer{
		namespace tool{
			class import{
			public:	
				import(std::string cmd);
				~import(void);
				
			private:
			void pushToDb(boost::filesystem::path p);
			//std::string path;
					
			}
		};
	}
}


#endif
