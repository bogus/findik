# New ports collection makefile for: 	findik	
# Date created:				Jul 18 2009
# Whom:					Burak OGUZ <burak.oguz@gmail.com>
#
# $FreeBSD$
#

PORTNAME= 	findik	
PORTVERSION=	0.2h	
CATEGORIES=	www
MASTER_SITES=   http://garr.dl.sourceforge.net/sourceforge/findik/	
DISTNAME=       findik-${PORTVERSION}
DISTFILES=      ${DISTNAME}.tar.gz

MAINTAINER?= 	findikmail@gmail.com	
COMMENT?= 	Content Filtering 	

LIB_DEPENDS= 	boost_thread.4:${PORTSDIR}/devel/boost \
	 	boost_system.4:${PORTSDIR}/devel/boost 
BUILD_DEPENDS=  tar:${PORTSDIR}/archivers/untar \
          	ungzip:${PORTSDIR}/archivers/gzip


OPTIONS=       	MYSQL_SUPPORT "Mysql Support for Blacklists" On \
               	CLAMD_SUPPORT "ClamAV Support" On \
	       	MAGIC_SUPPORT "Magic Number File Filter Support" On \
 		FILEEXT_SUPPORT "File Extension Filter" On \
		PCRE_SUPPORT "PCRE Content Filter" On \
		KERB5_SUPPORT "Kerberos5 Support" On \
		LDAP_SUPPORT "LDAP Support" On \
		SSL_SUPPORT "SSL Filtering Support" On \
		LIBCONFIG_SUPPORT "Advanced Configuration LIBCONFIG Support" On \
		BOOSTPO_SUPPORT "Boost Program Options Support" On \
		LOG4CXX_SUPPORT "Advanced Logging LOG4CXX Support" On

.include <bsd.port.options.mk>

.if defined(WITHOUT_MYSQL_SUPPORT)
CONFIGURE_ARGS+=    --enable-mysql=no --enable-simpledb=yes
.else
LIB_DEPENDS +=	mysqlpp.3:${PORTSDIR}/databases/mysql++3 
RUN_DEPENDS +=  ${LOCALBASE}/etc/rc.d/mysql-server:${PORTSDIR}/databases/mysql50-server
.endif
.if defined(WITHOUT_CLAMD_SUPPORT)
CONFIGURE_ARGS+=    --enable-clamdav=no
.else
RUN_DEPENDS +=    clamav:${PORTSDIR}/security/clamav
.endif
.if defined(WITHOUT_MAGIC_SUPPORT)
CONFIGURE_ARGS+=    --enable-magic=no
.endif
.if defined(WITHOUT_FILEEXT_SUPPORT)
CONFIGURE_ARGS+=    --enable-fileext=no
.endif
.if defined(WITHOUT_PCRE_SUPPORT)
CONFIGURE_ARGS+=    --enable-pcre=no
.else
LIB_DEPENDS +=	pcre.0:${PORTSDIR}/devel/pcre
.endif
.if defined(WITHOUT_LDAP_SUPPORT)
CONFIGURE_ARGS+=    --enable-ldap=no
.else
LIB_DEPENDS += ldap-2.4.3:${PORTSDIR}/net/openldap24-client 
.endif
.if defined(WITHOUT_SSL_SUPPORT)
CONFIGURE_ARGS+=    --enable-ssl=no
.endif
.if defined(WITHOUT_LIBCONFIG_SUPPORT)
CONFIGURE_ARGS+=    --enable-libconfig=no
.else
LIB_DEPENDS += config.8:${PORTSDIR}/devel/libconfig    
.endif
.if defined(WITHOUT_BOOSTPO_SUPPORT)
CONFIGURE_ARGS+=    --enable-boost-po=no
.else
LIB_DEPENDS +=	boost_program_options.4:${PORTSDIR}/devel/boost  
.endif
.if defined(WITHOUT_LOG4CXX_SUPPORT)
CONFIGURE_ARGS+=    --enable-log4cxx=no
.else
LIB_DEPENDS +=	log4cxx.9:${PORTSDIR}/devel/log4cxx  
.endif


WRKSRC=      ${WRKDIR}/${PORTNAME}-${PORTVERSION}
IS_INTERACTIVE=        yes
USE_GMAKE=     yes
GNU_CONFIGURE= yes

.include <bsd.port.mk>
