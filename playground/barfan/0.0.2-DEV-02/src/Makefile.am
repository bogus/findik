SUBDIRS = config filter io logging parser persistency

bin_PROGRAMS = findik

findik_SOURCES = findik.cpp

findik_LDADD = \
	config/*.o \
	config/libfindik_config.a \
	filter/*.o \
	filter/libfindik_filter.a \
	io/*.o \
	io/libfindik_io.a \
	logging/*.o \
	logging/libfindik_logging.a \
	parser/*.o \
	parser/libfindik_parser.a \
	persistency/*.o \
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
	-I@top_srcdir@/src/logging \
	-I@top_srcdir@/src/parser \
	-I@top_srcdir@/src/persistency
