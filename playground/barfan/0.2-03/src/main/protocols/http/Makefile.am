SUBDIRS                         =       auth_util
noinst_LTLIBRARIES		=	libfindik_http.la

libfindik_http_la_SOURCES	= \
	ad_kerb_negotiator.cpp \
	clamd_av_filter.cpp \
	content_mime_filter.cpp \
	data.cpp \
	domain_filter.cpp \
	domain_re_filter.cpp \
	file_ext_filter.cpp \
	html_content_filter.cpp \
	http_filter_logger.cpp \
	http_filter_result_generator.cpp \
	http_session_manager.cpp \
	https_authenticator.cpp \
	ldap_basic_authentication.cpp \
	request.cpp \
	request_parser.cpp \
	response.cpp \
	response_parser.cpp \
	url_filter.cpp \ 
	url_re_filter.cpp 

libfindik_http_la_LIBADD	=	@LTLIBOBJS@

INCLUDES 			= \
	-I@top_srcdir@/src/include/authenticator \
	-I@top_srcdir@/src/include/config \
	-I@top_srcdir@/src/include/filter \
	-I@top_srcdir@/src/include/io \
	-I@top_srcdir@/src/include/logging \
	-I@top_srcdir@/src/include/parser \
	-I@top_srcdir@/src/include/persistency \
	-I@top_srcdir@/src/include/protocols/http \
	-I@top_srcdir@/src/include/protocols/http/auth_util \
	-I@top_srcdir@/src/include/service \
	-I@top_srcdir@/src/include/util \
	-I/usr/include/mysql

