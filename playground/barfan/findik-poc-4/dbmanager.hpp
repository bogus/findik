#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace findik {
	class dbmanager {

	private:
		

	public:
		virtual void connectDb(std::string host, std::string db, 
			std::string username, std::string password) = 0;
		virtual bool domainQuery(std::string hostname) = 0;
		virtual bool urlQuery(std::string url) = 0;
		virtual bool contentQuery(std::string content) = 0;
		virtual bool domainRegexQuery(std::string hostname) = 0;
		virtual bool urlRegexQuery(std::string url) = 0;
		virtual bool contentRegexQuery(std::string content) = 0;

		std::string host;
		std::string db;
		std::string username;
		std::string password;

	};
}