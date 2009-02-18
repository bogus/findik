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

#include "ad_kerb_negotiator.hpp"
#include "base64.hpp"
#include "spnegokrb5.h"
#include <krb5.h>
#include <gssapi/gssapi.h>
#include <gssapi/gssapi_generic.h>
#include <gssapi/gssapi_krb5.h>

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			// initialization of logger
			log4cxx::LoggerPtr ad_kerb_negotiator::debug_logger(log4cxx::Logger::getLogger("findik.protocols.http.ad_kerb_negotiator"));	
			int ad_kerb_negotiator::authenticator_code = 101;
			// constructor definition of filter service registration inner class
			ad_kerb_negotiator::initializer::initializer()
                        {
                                ad_kerb_negotiator_ptr akn(new ad_kerb_negotiator());

                                FI_SERVICES->authentication_srv().register_authenticator(akn);
                        }

                        ad_kerb_negotiator::initializer ad_kerb_negotiator::initializer::instance;

			boost::tuple<bool, findik::authenticator::authentication_result_ptr> ad_kerb_negotiator::authenticate(findik::io::connection_ptr connection_) 
			{
				LOG4CXX_DEBUG(debug_logger, "AD Kerberos v5 Negotiator entered"); // log for filter entrance
						
				// get request object from current data
				request_ptr req = boost::static_pointer_cast<request>(connection_->current_data());
				std::string auth = "";
				
				// get hostname from request header
				BOOST_FOREACH( header h, req->get_headers() ) {
					if (h.name == "Proxy-Authorization") {
						auth = h.value;
						std::cout << "+++++++++++++++++\n" << auth << std::endl << "+++++++++++++++++\n";  
					}
				}
				if( auth == "")
					return boost::make_tuple(false, findik::authenticator::authentication_result::create_result(authenticator_code,"Not authorized", 401, false, findik::io::http));	
				else {
					OM_uint32 major_status, minor_status, minor_status2;
					gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
					gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  					const char *auth_param = NULL;
  					int ret;
					gss_name_t client_name = GSS_C_NO_NAME;
					gss_cred_id_t delegated_cred = GSS_C_NO_CREDENTIAL;
					
					gss_OID_desc spnego_oid;
					gss_ctx_id_t context = GSS_C_NO_CONTEXT;
					gss_cred_id_t server_creds = GSS_C_NO_CREDENTIAL;
					OM_uint32 ret_flags = 0;

					std::string negotiate_ret_value = "\0";

					spnego_oid.length = 6;
					spnego_oid.elements = (void *)"\x2b\x06\x01\x05\x05\x02";

					putenv("KRB5_KTNAME=/etc/findik/x.keytab");

					gsskrb5_register_acceptor_identity("/etc/findik/x.keytab");

					gss_buffer_desc token = GSS_C_EMPTY_BUFFER;
					gss_name_t server_name = GSS_C_NO_NAME;
					std::string buf = "HTTP/webfilter1.burakoguz.net@BURAKOGUZ.NET";
					int have_server_princ;

					token.value = (void *)buf.c_str();
					token.length = buf.length();

					major_status = gss_import_name(&minor_status, &token,(gss_OID) GSS_KRB5_NT_PRINCIPAL_NAME, &server_name);
					memset(&token, 0, sizeof(token));

					if (GSS_ERROR(major_status)) {
					      std::cout << "+++++++++++++++++++\nHATAAAA 1\n++++++++++++++++\n";  
					}
			
					major_status = gss_display_name(&minor_status, server_name, &token, NULL);

					if (GSS_ERROR(major_status)) {
                                              std::cout << "+++++++++++++++++++\nHATAAAA 2\n++++++++++++++++\n";
                                        }
			
					gss_release_buffer(&minor_status, &token);

					major_status = gss_acquire_cred(&minor_status, server_name, GSS_C_INDEFINITE,
		                        	           GSS_C_NO_OID_SET, GSS_C_ACCEPT,
                			                   &server_creds, NULL, NULL);
					
					gss_release_name(&minor_status2, &server_name);
	
					if (GSS_ERROR(major_status)) {
                                              std::cout << "+++++++++++++++++++\nHATAAAA 3\n++++++++++++++++\n";
                                        }
			
					std::cout << auth.substr(10) << std::endl;			
		
					std::string input_token_str = base64_decode(auth.substr(10));					
					input_token.value = (void *)input_token_str.c_str();
					input_token.length = input_token_str.length();

					major_status = gss_accept_sec_context_spnego(&minor_status,
	                                  &context, server_creds, &input_token, GSS_C_NO_CHANNEL_BINDINGS, 
		                	  &client_name, NULL, &output_token, &ret_flags, NULL, &delegated_cred);

					if (GSS_ERROR(major_status)) {
						if (input_token.length > 7 && memcmp(input_token.value, "NTLMSSP", 7) == 0) {
							std::cout <<"Warning: received token seems to be NTLM, which isn't supported by the Kerberos module. Check your IE configuration."<< std::endl;
							return boost::make_tuple(true, findik::authenticator::authentication_result::create_result(0));	
						
						}
						std::cout << "+++++++++++++++++++\nHATAAAA 4 -- "<< auth.substr(10).length() << " -- " << input_token_str.length();
						printf("\nMajor : %8.8x - Minor: %8.8x\n",major_status,minor_status);
						std::cout <<"\n++++++++++++++++\n";
					}

					major_status = gss_display_name(&minor_status, client_name, &output_token, NULL);
					if (GSS_ERROR(major_status)) {
						std::cout << "+++++++++++++++++++\nHATAAAA 5";
						printf("\nMajor : %8.8x - Minor: %8.8x\n",major_status,minor_status);
						std::cout <<"\n++++++++++++++++\n";	
					}
					gss_release_name(&minor_status, &client_name);
                                        std::cout << "+++++++++++++++++++\n"<< (char *)output_token.value  <<"\n++++++++++++++++\n";

					if (output_token.length) {
						
					}

				}
					
			}

                        findik::io::protocol ad_kerb_negotiator::proto()
			{
				// set this filter to be used in request only
				return findik::io::http;	
			}
		}
	}
}

