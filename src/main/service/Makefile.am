noinst_LTLIBRARIES		=	libfindik_service.la

libfindik_service_la_SOURCES	= \
	authentication_service.cpp \
	filter_service.cpp \
	parser_service.cpp \
	pcre_service.cpp \
	reply_service.cpp \
	magic_num_service.cpp \
	service_chain_element.cpp \
	service_container.cpp \
	session_service.cpp \
	util_service.cpp

libfindik_service_la_LIBADD	=	@LTLIBOBJS@

INCLUDES 			= \
	-I@top_srcdir@/src/include/authenticator \
	-I@top_srcdir@/src/include/config \
	-I@top_srcdir@/src/include/filter \
	-I@top_srcdir@/src/include/io \
	-I@top_srcdir@/src/include/logging \
	-I@top_srcdir@/src/include/parser \
	-I@top_srcdir@/src/include/persistency \
	-I@top_srcdir@/src/include/service \
	-I@top_srcdir@/src/include/util \
	-I/usr/include/mysql
