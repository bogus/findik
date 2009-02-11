noinst_LTLIBRARIES		=	libfindik_http.la

libfindik_http_la_SOURCES	= \
	data.cpp \
	domain_filter.cpp \
	domain_re_filter.cpp \
	html_content_filter.cpp \
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
	-I@top_srcdir@/src/include/service \
	-I@top_srcdir@/src/include/util 

