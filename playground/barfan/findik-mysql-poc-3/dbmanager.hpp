#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace findik {
	class dbmanager {

	private:
		std::string host;
		std::string db;
		std::string username;
		std::string password;

	public:
		virtual void connectDb(std::string host, std::string db, 
			std::string username, std::string password) = 0;
		virtual bool hostnameQuery(std::string hostname) = 0;
		virtual bool contentQuery(std::string content) = 0;
		virtual bool hostnameRegexQuery(std::string hostname) = 0;
		virtual bool contentRegexQuery(std::string content) = 0;

	};
}