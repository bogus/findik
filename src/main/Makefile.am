SUBDIRS = authenticator config filter logging io parser persistency protocols service util

lib_LTLIBRARIES		=	libfindik.la

libfindik_la_SOURCES	=
libfindik_la_LDFLAGS	=	-no-undefined -version-info 0:0:0
libfindik_la_LIBADD	= \
	authenticator/libfindik_authenticator.la \
	config/libfindik_config.la \
	filter/libfindik_filter.la \
	logging/libfindik_logging.la \
	io/libfindik_io.la \
	parser/libfindik_parser.la \
	persistency/libfindik_persistency.la \
	protocols/http/libfindik_http.la \
	service/libfindik_service.la \
	util/libfindik_util.la

bin_PROGRAMS		=	findik
findik_SOURCES		=	findik.cpp
findik_LDADD		=	libfindik.la

LIBS = \
	-lboost_thread \
	-lboost_system \
	-lpthread \
	-llog4cxx \
	-lconfig++ \
	-lz \
	-ltidy \
	-lmagic \
	-lpcrecpp \
	-lmysqlpp

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

