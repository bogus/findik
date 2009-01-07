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
				
				
				findik::importer::persistence::dbmanager::pointer dbmanager_ =
                		findik::importer::persistence::dbmanager::pointer(new findik::importer::persistence::mysqldbmanager());
        			dbmanager_->connectDb();
        			int category_id = dbmanager_->newCategory(p.leaf());

        			//dbmanager_->newDomain("www.live.com",category_id);
        			//dbmanager_->newUrl("http://www.zen-cart.com/forum/showthread.php?t=40052",category_id);
				//std::cout<<p.leaf()<<std::endl;
				boost::filesystem::path temp(p);
				temp /= "domains";
				if(boost::filesystem::exists(temp))
				{
					std::string fpath(temp.string()); 
					std::string line;
					std::ifstream inp(fpath.c_str());
					while(!inp.eof())
					{
						inp>>line;
        					dbmanager_->newDomain(line,category_id);
					}
					
				}
				
			}
		}
	}
}
