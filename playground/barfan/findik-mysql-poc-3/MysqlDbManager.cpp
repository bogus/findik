#include "MysqlDbManager.h"

MysqlDbManager::MysqlDbManager() {

}

void MysqlDbManager::connectDb(std::string host, std::string db, std::string username, std::string password) {

}

bool MysqlDbManager::contentQuery(std::string content) {
	std::cout << content << std::endl;
	return true;
}

bool MysqlDbManager::contentRegexQuery(std::string content) {
	return true;
}

bool MysqlDbManager::hostnameQuery(std::string hostname) {
	return true;
}

bool MysqlDbManager::hostnameRegexQuery(std::string hostname) {
	return true;
}