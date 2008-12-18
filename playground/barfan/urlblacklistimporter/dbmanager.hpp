#ifndef FINDIK_IMPORTER_PERSISTENCE_DBMANAGER_HPP
#define FINDIK_IMPORTER_PERSISTENCE_DBMANAGER_HPP

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace importer {
		namespace persistence {
			
			class dbmanager :
				public boost::enable_shared_from_this<dbmanager>
			{
			public:

				virtual void connectDb() = 0;
				virtual int newCategory(std::string category_name) = 0;
				virtual int newDomain(std::string domain_name,int category_id) = 0;
				virtual int newUrl(std::string url_name,int category_id) = 0;

				typedef boost::shared_ptr<dbmanager> pointer;

			protected:
				std::string host;
				std::string db;
				std::string username;
				std::string password;

			};

		}
	}
}

#endif
