#ifndef FINDIK_DBMANAGER_HPP
#define FINDIK_DBMANAGER_HPP

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace persistency {
		class dbmanager :
			public boost::enable_shared_from_this<dbmanager>
		{

		private:
			

		public:
			virtual void connectDb() = 0;
			virtual bool domainQuery(std::string hostname) = 0;
			virtual bool urlQuery(std::string url) = 0;
			virtual bool contentQuery(std::string content) = 0;
			virtual bool domainRegexQuery(std::string hostname) = 0;
			virtual bool urlRegexQuery(std::string url) = 0;
			virtual bool contentRegexQuery(std::string content) = 0;

			typedef boost::shared_ptr<dbmanager> pointer;

		protected:
			std::string host;
			std::string db;
			std::string username;
			std::string password;

		};
	}
}

#endif
