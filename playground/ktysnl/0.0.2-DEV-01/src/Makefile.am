SUBDIRS = config filter io logging parser persistency urlblacklistimporter

lib_LTLIBRARIES		=	libfindik.la

libfindik_la_SOURCES	=
libfindik_la_LDFLAGS	=	-no-undefined -version-info 0:0:0
libfindik_la_LIBADD	= \
	config/libfindik_config.la \
	filter/libfindik_filter.la \
	io/libfindik_io.la \
	logging/libfindik_logging.la \
	parser/libfindik_parser.la \
	persistency/libfindik_persistency.la

bin_PROGRAMS		= \
	findik \
	importer

findik_SOURCES		=	findik.cpp
findik_LDADD		=	libfindik.la

importer_SOURCES	=	urlblacklistimporter/main.cpp


LIBS = \
	-lboost_thread \
	-lboost_system \
	-lpthread \
	-llog4cxx \
	-lconfig++ \
	-lz \
	-ltidy \
	-lmysqlcppconn\
	-lboost_filesystem

INCLUDES = \
	-I@top_srcdir@/src/config \
	-I@top_srcdir@/src/filter \
	-I@top_srcdir@/src/io \
	-I@top_srcdir@/src/logging \
	-I@top_srcdir@/src/parser \
	-I@top_srcdir@/src/persistency\
	-I@top_srcdir@/src/urlblacklistimporter
