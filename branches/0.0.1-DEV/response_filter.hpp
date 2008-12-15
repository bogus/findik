#include "mysqldbmanager.hpp"
#include "response.hpp"

namespace findik {
	namespace filter{
		class response_filter
		{
		public:
			response_filter(dbmanager *manager_,io::response *response_);
			~response_filter(void);
			bool response_chain_filter();

		private:
			io::response * response_;
			dbmanager * manager_;

			bool response_content_filter();
			bool response_content_type_filter();

		};
	}
}