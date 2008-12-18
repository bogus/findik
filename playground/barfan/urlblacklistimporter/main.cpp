#include "configuration.hpp"
#include "mysqldbmanager.hpp"

int main()
{
	findik::importer::persistence::dbmanager::pointer dbmanager_ = 
		findik::importer::persistence::dbmanager::pointer(new findik::importer::persistence::mysqldbmanager());
	dbmanager_->connectDb();
	int category_id = dbmanager_->newCategory("burak1");
	dbmanager_->newDomain("www.live.com",category_id);
	dbmanager_->newUrl("http://www.zen-cart.com/forum/showthread.php?t=40052",category_id);

	char c;

	std::cin >> c;
}