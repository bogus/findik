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

				boost::filesystem::path temp(p);
				temp /= "domains";
				
				std::string line;
				std::string fpath(temp.string());
				if(boost::filesystem::exists(temp))
				{
					
					std::ifstream inp(fpath.c_str());
					while(!inp.eof())
					{
						inp>>line;
						
						
        					dbmanager_->newDomain(line,category_id);

					}
					inp.close();
				}

				
				temp = p;
				temp /= "urls";
				fpath = temp.string();
				if(boost::filesystem::exists(temp))
				{
					
					
					
					std::ifstream inp(fpath.c_str());
					while(!inp.eof())
					{
						inp>>line;
						
						
        					dbmanager_->newUrl(line,category_id);

					}
					inp.close();
				}	
			}
		}
	}
}

