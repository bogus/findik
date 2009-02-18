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

#include "reply_service.hpp"
#include "service_container.hpp"
#include <time.h>
#include <iostream>
#include <sstream>

namespace findik
{
	namespace service
	{
		reply_service::reply_service()
		{
			stock_replies_[findik::io::http][FC_BAD_LOCAL] = "Bad request!";
			stock_replies_[findik::io::http][FC_BAD_REMOTE] = "Bad response!";

			std::string reply_file_name;
			// FI_SERVICES->config_srv().getConfigValue_String("findik.reply.reply_file", reply_file_name);
			
			std::string line;
			std::ifstream file ("/etc/index.html");
			if (file.is_open())
			{
				while (!file.eof())
				{
					getline (file,line);
					reply_html_.append(line);
				}
				file.close();
			}
		}

		reply_service::~reply_service()
		{}

		void reply_service::reply(boost::asio::streambuf & sbuf,
				findik::io::protocol proto, unsigned int code)
		{
			std::ostream os(&sbuf);
			os << stock_replies_[proto][code];
		}

		void reply_service::reply(boost::asio::streambuf & sbuf,
				findik::io::protocol proto, findik::filter::filter_reason_ptr reason)
		{
			// TODO: reply generator chain .
			std::ostream os(&sbuf);
			std::string resp;

			if(reason->protocol() == findik::io::http)
			{
				std::ostringstream stm;
				std::string reply_str_(reply_html_);
				time_t rawtime;
				time(&rawtime);

				resp = "HTTP/1.1 ";
				if(reason->return_code() == 403) {
					resp = resp + "403 Forbidden\r\n"; 
				} else {
					resp = resp + "404 Not Found\r\n"; 
				}

				if(reason->close_connection()) {
					FI_SERVICES->util_srv().pcre().global_replace("@@date@@", ctime(&rawtime), reply_str_);	
					FI_SERVICES->util_srv().pcre().global_replace("@@reason@@", reason->reason_str() , reply_str_);
					stm << reply_str_.length();
					resp = resp + "Content-Type : text/html \r\n";				
					resp = resp + "Connection : close\r\n\r\n";
					resp = resp + reply_str_;	
				} else {
					resp = resp + "Content-Length : 0\r\n\r\n";	
				}
			}

			os << resp;
		}

		void reply_service::reply(boost::asio::streambuf & sbuf,
				findik::io::protocol proto, findik::authenticator::authentication_result_ptr reason)
		{
			// TODO: reply generator chain .
			std::ostream os(&sbuf);
			std::string resp;

                        if(reason->protocol() == findik::io::http)
                        {
                                std::ostringstream stm;
                                std::string reply_str_(reply_html_);
                                time_t rawtime;
                                time(&rawtime);
                                resp = "HTTP/1.1 ";
                                if(reason->return_code() == 401) {
					char datetime[50];
					sprintf(datetime, "Date: Wed, 18 Feb 2009 %d:%d:%d GMT\r\n",gmtime(&rawtime)->tm_hour, gmtime(&rawtime)->tm_min, gmtime(&rawtime)->tm_sec); 
                                        resp = resp + "407 Proxy Authentication Required\r\n";
					resp = resp + "Proxy-Authenticate: Negotiate\r\n";	
					resp = resp + datetime;	
					resp = resp + "Content-Length : 0\r\n";	
					resp = resp + "Proxy-Connection: close  \r\n";	
                                } else {
                                        resp = resp + "404 Not Found\r\n";
                                }
			}

			os << resp;
		}
	}
}

