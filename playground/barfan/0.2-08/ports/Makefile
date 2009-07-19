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
RUN_DEPENDS=	bash:${PORTSDIR}/shells/bash \
		logrotate:${PORTSDIR}/sysutils/logrotate

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
RUN_DEPENDS +=  mysql:${PORTSDIR}/databases/mysql50-client
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
#USE_GMAKE=     yes
GNU_CONFIGURE= yes

LOGSDIR?=       /var/log/findik
LOGROTATEDIR?=     /usr/local/etc/logrotate.d 

post-install:
${MKDIR} ${LOGSDIR}/
${MKDIR} ${LOGROTATEDIR}/
@cp ${WRKSRC}/packaging/redhat/findik.logrotate ${LOGROTATEDIR}/findik

/usr/local/bin/bash

(/usr/local/etc/rc.d/mysql-server status) || (/usr/local/etc/rc.d/mysql-server start) 

# Import MySQL schema
if (echo|mysql); then
        if [ -z "$(echo 'show databases'|mysql|grep -e '^findik$')" ]; then
                ( mysqladmin create findik && \
                mysql findik < /usr/local/share/findik/sql/schema.sql ) || ( \
                echo "==========================================================="; \
                echo "|   A problem occured while importing schema.   		|"; \
                echo "|   Please create a database and import         		|"; \
                echo "|   /usr/local/share/findik/sql/schema.sql manually.  	|"; \
                echo "==========================================================="; \
                echo; )
        else
                echo "==========================================================="
                echo "|   A database named 'findik' exists on MySQL.  		|"
                echo "|   Please create a database and import         		|"
                echo "|   /usr/local/share/findik/sql/schema.sql manually.  	|"
                echo "==========================================================="
                echo
        fi
else
        echo "==========================================================="
        echo "|   Can not access MySQL.                       		|"
        echo "|   Please create a database and import         		|"
        echo "|   /usr/local/share/findik/sql/schema.sql manually.  	|"
        echo "|   Also, edit MySQL credentials in             		|"
        echo "|   /usr/local/etc/findik/findik.cfg .                    |"
        echo "==========================================================="
        echo
fi

if [ ! -f /usr/local/etc/findik/ssl/public.pem -a ! -f /usr/local/etc/findik/ssl/private.pem -a ! -f /usr/local/etc/findik/ssl/dh.pem ]; then
        if (echo -e "ME\nRohan\nCalenardhon\nRohirrim\n\n*\nrohirrim@example.com\n"| \
                /usr/local/share/findik/scripts/generate-ssl-keys /etc/findik/ssl 512); then
                echo "==========================================================="
                echo "|   Created initial SSL keys and 512-byte DH    		|"
                echo "|   parameters. If you want to recreate them,   		|"
                echo "|   you can call                                		|"
                echo "|   /usr/local/share/findik/scripts/generate-ssl-keys 	|"
                echo "==========================================================="
                echo
        else
                echo "==========================================================="
                echo "|   A problem occured during key generation.    		|"
                echo "|   Please recall and inspect output of         		|"
                echo "|   /usr/local/share/findik/scripts/generate-ssl-keys 	|"
                echo "|   command.                                    		|"
                echo "==========================================================="
                echo
        fi
else
        echo "==========================================================="
        echo "|   Found SSL keys at /usr/local/etc/findik/ssl/ and      |"
        echo "|   kept unchanged. If you want to recreate     		|"
        echo "|   them, you can call                          		|"
        echo "|   /usr/local/share/findik/scripts/generate-ssl-keys 	|"
        echo "==========================================================="
        echo
fi

echo "findik_enable=\"YES\"" >> /etc/rc.conf 

sed 's@"/etc/findik@"/usr/local/etc/findik@' </usr/local/etc/findik/findik.cfg >/usr/local/etc/findik/findik.cfg.bsd ; mv /usr/local/etc/findik/findik.cfg.bsd /usr/local/etc/findik/findik.cfg 

.include <bsd.port.mk>
