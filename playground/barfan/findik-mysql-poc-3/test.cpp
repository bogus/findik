#include "mysqldbmanager.hpp"

using namespace std;

int main() {

	
	findik::dbmanager *manager = new findik::mysqldbmanager();
	manager->contentQuery("ali");

	char c;

	cin >> c;

}