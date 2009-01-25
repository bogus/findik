SUBDIRS = config filter logging io parser service

lib_LTLIBRARIES		=	libfindik.la

libfindik_la_SOURCES	=
libfindik_la_LDFLAGS	=	-no-undefined -version-info 0:0:0
libfindik_la_LIBADD	= \
	config/libfindik_config.la \
	filter/libfindik_filter.la \
	logging/libfindik_logging.la \
	io/libfindik_io.la \
	parser/libfindik_parser.la \
	service/libfindik_service.la

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
	-lmysqlcppconn

INCLUDES = \
	-I@top_srcdir@/src/main/config \
	-I@top_srcdir@/src/main/filter \
	-I@top_srcdir@/src/main/logging \
	-I@top_srcdir@/src/main/io \
	-I@top_srcdir@/src/main/parser \
	-I@top_srcdir@/src/main/service
