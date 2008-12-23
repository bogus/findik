SUBDIRS = config filter io parser persistency

bin_PROGRAMS = findik

findik_SOURCES = \
	findik.cpp \
	log_initializer.cpp

findik_LDADD = \
	config/libfindik_config.a \
	filter/libfindik_filter.a \
	io/libfindik_io.a \
	parser/libfindik_parser.a \
	persistency/libfindik_persistency.a 

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
	-I@top_srcdir@/src/config \
	-I@top_srcdir@/src/filter \
	-I@top_srcdir@/src/io \
	-I@top_srcdir@/src/parser \
	-I@top_srcdir@/src/persistency
