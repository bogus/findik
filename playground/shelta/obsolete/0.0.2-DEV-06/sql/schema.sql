-- MySQL dump 10.13  Distrib 5.1.30, for Win32 (ia32)
--
-- Host: localhost    Database: findik
-- ------------------------------------------------------
-- Server version	5.1.30-community

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES latin1 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `blacklist_content`
--

DROP TABLE IF EXISTS `blacklist_content`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `blacklist_content` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `content` varchar(128) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `content` USING HASH(`content`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `blacklist_content`
--

LOCK TABLES `blacklist_content` WRITE;
/*!40000 ALTER TABLE `blacklist_content` DISABLE KEYS */;
/*!40000 ALTER TABLE `blacklist_content` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `blacklist_domain`
--

DROP TABLE IF EXISTS `blacklist_domain`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = latin1;
CREATE TABLE `blacklist_domain` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `domain` varchar(128) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `domain` USING HASH (`domain`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `blacklist_domain`
--

LOCK TABLES `blacklist_domain` WRITE;
/*!40000 ALTER TABLE `blacklist_domain` DISABLE KEYS */;
INSERT INTO `blacklist_domain` VALUES (1,'www.live.com',1,1);
/*!40000 ALTER TABLE `blacklist_domain` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `blacklist_url`
--

DROP TABLE IF EXISTS `blacklist_url`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = latin1;
CREATE TABLE `blacklist_url` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `url` varchar(512) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `url` USING HASH (`url`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `blacklist_url`
--

LOCK TABLES `blacklist_url` WRITE;
/*!40000 ALTER TABLE `blacklist_url` DISABLE KEYS */;
/*!40000 ALTER TABLE `blacklist_url` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = latin1;
CREATE TABLE `category` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `catname` varchar(128) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `catname` USING HASH (`catname`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` VALUES (1,'search engine');
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `whitelist_content`
--

DROP TABLE IF EXISTS `whitelist_content`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `whitelist_content` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `content` varchar(128) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `content` USING HASH (`content`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `whitelist_content`
--

LOCK TABLES `whitelist_content` WRITE;
/*!40000 ALTER TABLE `whitelist_content` DISABLE KEYS */;
/*!40000 ALTER TABLE `whitelist_content` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `whitelist_domain`
--

DROP TABLE IF EXISTS `whitelist_domain`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = latin1;
CREATE TABLE `whitelist_domain` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `domain` varchar(128) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `domain` USING HASH (`domain`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `whitelist_domain`
--

LOCK TABLES `whitelist_domain` WRITE;
/*!40000 ALTER TABLE `whitelist_domain` DISABLE KEYS */;
/*!40000 ALTER TABLE `whitelist_domain` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `whitelist_url`
--

DROP TABLE IF EXISTS `whitelist_url`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = latin1;
CREATE TABLE `whitelist_url` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `url` varchar(512) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `url` USING HASH (`url`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `whitelist_url`
--

LOCK TABLES `whitelist_url` WRITE;
/*!40000 ALTER TABLE `whitelist_url` DISABLE KEYS */;
/*!40000 ALTER TABLE `whitelist_url` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2008-12-21 10:31:01
