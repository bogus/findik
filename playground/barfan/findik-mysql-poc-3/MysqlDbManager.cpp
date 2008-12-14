#include "mysqldbmanager.hpp"

mysqldbmanager::mysqldbmanager() {

}

void mysqldbmanager::connectDb(std::string host, std::string db, std::string username, std::string password) {

}

bool mysqldbmanager::contentQuery(std::string content) {
	std::cout << content << std::endl;
	return true;
}

bool mysqldbmanager::contentRegexQuery(std::string content) {
	return true;
}

bool mysqldbmanager::hostnameQuery(std::string hostname) {
	return true;
}

bool mysqldbmanager::hostnameRegexQuery(std::string hostname) {
	return true;
}