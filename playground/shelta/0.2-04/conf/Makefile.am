findikconfdir = $(sysconfdir)/findik
findikconfssldir = $(findikconfdir)/ssl

findikconf_DATA = \
	findik.cfg \
	findik_log.conf \
	index.html \
	ssl.html

findikconfssl_DATA = \
	ssl/ca.pem

DISTCLEANFILES = \
	$(findikconf_DATA) \
	$(findikconfssl_DATA)

EXTRA_DIST = \
	$(findikconf_DATA) \
	$(findikconfssl_DATA)
	
