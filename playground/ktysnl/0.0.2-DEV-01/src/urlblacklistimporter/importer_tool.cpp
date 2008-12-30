#include "importer_tool.hpp"

namespace findik{
        namespace importer{
                namespace tool{
			import::import(std::string cmd){
				boost::filesystem::path p(cmd);
				boost::filesystem::directory_iterator d1(p), d2;
        			for(; d1 != d2; ++d1)
       			 	 {
                			if( boost::filesystem::is_directory(d1->path()) )
               				 {
						pushToDb(d1->path());
				         }
				 }
			}
			import::~import(void){
			}

			void import::pushToDb(boost::filesystem::path p)
			{
				
				std::cout<<p.string();
				
			}
		}
	}
}
