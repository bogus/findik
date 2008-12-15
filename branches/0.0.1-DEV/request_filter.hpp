#include "mysqldbmanager.hpp"
#include "request.hpp"

namespace findik {
	namespace filter {
		class request_filter
		{
		public:
			~request_filter(void);
			request_filter(dbmanager *manager_, io::request *request_);
			bool request_chain_filter();

		private:
			io::request *request_ ;
			dbmanager * manager_ ;

			bool request_domain_filter();
			bool request_url_filter();
			bool request_content_filter();

		};
	}
}
