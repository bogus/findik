/*
  Copyright (C) 2008 Burak OGUZ (barfan) <findikmail@gmail.com>

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

#include "ldap_basic_authentication.hpp"
#include "base64.hpp"
#include <ldap.h>

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			// initialization of logger
			log4cxx::LoggerPtr ldap_basic_authentication::debug_logger(log4cxx::Logger::getLogger("findik.protocols.http.ldap_basic_authentication"));	
			int ldap_basic_authentication::authenticator_code = 102;
			// constructor definition of filter service registration inner class
			ldap_basic_authentication::initializer::initializer()
                        {
                                ldap_basic_authentication_ptr akn(new ldap_basic_authentication());
				if(FI_CONFIG.use_ldap_basic_auth())
	                                FI_SERVICES->authentication_srv().register_authenticator(akn);
                        }

                        ldap_basic_authentication::initializer ldap_basic_authentication::initializer::instance;

			boost::tuple<bool, findik::authenticator::authentication_result_ptr> ldap_basic_authentication::authenticate(findik::io::connection_ptr connection_) 
			{
				LOG4CXX_DEBUG(debug_logger, "LDAP Basic Authenticator entered"); // log for filter entrance
						
				// get request object from current data
				request_ptr req = boost::static_pointer_cast<request>(connection_->current_data());
				std::string auth = "";
				
				// get hostname from request header
				BOOST_FOREACH( header h, req->get_headers() ) {
					if (h.name == "Proxy-Authorization") {
						auth = h.value;
					}
				}
				if( auth == "")
					return boost::make_tuple(false, findik::authenticator::authentication_result::create_result(authenticator_code,"Proxy authorization required", authenticator_code, false, findik::io::http));	
				else {
					std::cout << "********\n" << base64_decode(auth.substr(6)) << std::endl;
					LDAP *ld = (LDAP *) NULL;
					LDAPMessage *result = (LDAPMessage *) NULL;
					std::string base_dn = FI_CONFIG.ldap_base_dn();
					int rc = -1;
					struct berval cred;
					std::string bind_dn_name = FI_CONFIG.ldap_bind_dn_name();
					std::string bind_dn_pass = FI_CONFIG.ldap_bind_dn_password();

					cred.bv_len=bind_dn_pass.length();
					cred.bv_val=(char *)bind_dn_pass.c_str();


					rc = ldap_initialize (&ld, FI_CONFIG.ldap_server_name().c_str());

					if (rc != LDAP_SUCCESS)
					{
						printf("Could not initiazlize LDAP, reason: %s\n",ldap_err2string(rc));
						return 0;
					}


					rc=ldap_sasl_bind_s(ld,bind_dn_name.c_str(),NULL,&cred,NULL,NULL,NULL);
					if (rc != LDAP_SUCCESS)
					{
						printf("Could not bind to LDAP server, reason: %s\n",ldap_err2string(rc));
						return 0;
					}

					char *attrs[2];
					attrs[0] = (char *)FI_CONFIG.ldap_password_attr().c_str();
					attrs[1] = NULL;

					struct timeval tv;

					tv.tv_sec=60*60;
					tv.tv_usec=0;

					int msgid;
					
					rc = ldap_search_ext(ld,
							base_dn.c_str(),
							LDAP_SCOPE_SUBTREE,
							("(&(objectClass=*)(uid=" +  base64_decode(auth.substr(6)) + "))").c_str(),
							attrs, 0,NULL,NULL,&tv,1000000,
							&msgid);

					if (rc != LDAP_SUCCESS)
					{
						printf("Could not search LDAP server, reason: %s",ldap_err2string(rc));
					}

					tv.tv_sec=30;
					tv.tv_usec=0;

					rc=ldap_result(ld, msgid, 0, &tv, &result);

					LDAPMessage *entry =ldap_first_message(ld,result);

					struct berval **n_val = ldap_get_values_len(ld, entry, FI_CONFIG.ldap_password_attr().c_str());

					if(n_val != NULL)
						std::cout << n_val[0]->bv_val << std::endl;


					return boost::make_tuple(true, findik::authenticator::authentication_result::create_result(0));
				}

			}

			findik::io::protocol ldap_basic_authentication::proto()
			{
				// set this filter to be used in request only
				return findik::io::http;	
			}
		}
	}
}

