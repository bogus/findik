SUBDIRS=config filter io parser persistency

bin_PROGRAMS = findik
findik_SOURCES = \
	findik.cpp \
	log_initializer.cpp
findik_LDADD = \
	config/libfindik_config.a \
	filter/libfindik_filter.a \
	io/libfindik_io.a \
	parser/libfindik_parser.a \
	parser/libfindik_persistency.a 
