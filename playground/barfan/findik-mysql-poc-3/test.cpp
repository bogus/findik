#include "MysqlDbManager.h"

using namespace std;

int main() {

	DbManager *manager = new MysqlDbManager();
	manager->contentQuery("ali");

	char c;

	cin >> c;

}