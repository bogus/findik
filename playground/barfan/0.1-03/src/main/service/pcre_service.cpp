/*
  Copyright (C) 2008 H. Kerem Cevahir (shelta) <findikmail@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "pcre_service.hpp"
#include "pcre_analyzer.hpp"
#include "service_container.hpp"

namespace findik
{
	namespace service
	{
		pcre_service::pcre_service() 
		{}

		pcre_service::~pcre_service() 
		{}

		void pcre_service::start()
		{
			std::map<int,std::string> pcre_map;
                        FI_SERVICES->db_srv().pcreQuery(pcre_map);
                        for(std::map<int,std::string>::iterator iter = pcre_map.begin(); iter != pcre_map.end(); iter++)
                        {
                                re_vector.push_back(new findik::util::pcre_parser(iter->first,iter->second));
                        }

		}

		std::vector<findik::util::pcre_analyzer> pcre_service::matches_predefined(std::string data)
		{
			bool isOk = true;
			
			pcrecpp::StringPiece *input = new pcrecpp::StringPiece(data);
			std::string match;
			std::vector<findik::util::pcre_analyzer> results;

			for( int i = 0, j = 0; i < re_vector.size(); i++ ) {
				while(re_vector[i]->get_re()->FindAndConsume(input,&match)) {
					std::transform(match.begin(), match.end(), match.begin(), tolower);
					for(j = 0; j < results.size(); j++) {
						if(results[j].get_word() == match) {
							results[j].set_count(results[j].get_count()+1);
							break;
						}	
					}
					if(j == results.size()) {
						findik::util::pcre_analyzer analyzer;
						analyzer.set_word(match);
						analyzer.set_count(1);
						analyzer.set_catid(re_vector[i]->get_category_id());
						results.push_back(analyzer);
					}
				}
			}
			
			return results;

		}

	}
}

