-- MySQL dump 10.11
--
-- Host: localhost    Database: findik
-- ------------------------------------------------------
-- Server version	5.0.45

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `acl_filter_param`
--

DROP TABLE IF EXISTS `acl_filter_param`;
CREATE TABLE `acl_filter_param` (
  `id` int(11) NOT NULL auto_increment,
  `rule_id` int(11) NOT NULL,
  `filter_key` varchar(32) NOT NULL,
  `param` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `rule_id` (`rule_id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `acl_filter_param`
--

LOCK TABLES `acl_filter_param` WRITE;
/*!40000 ALTER TABLE `acl_filter_param` DISABLE KEYS */;
/*!40000 ALTER TABLE `acl_filter_param` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `acl_ip_cross`
--

DROP TABLE IF EXISTS `acl_ip_cross`;
CREATE TABLE `acl_ip_cross` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `rule_id` int(10) unsigned NOT NULL,
  `acl_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `acl_ip_cross`
--

LOCK TABLES `acl_ip_cross` WRITE;
/*!40000 ALTER TABLE `acl_ip_cross` DISABLE KEYS */;
/*!40000 ALTER TABLE `acl_ip_cross` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `acl_rule`
--

DROP TABLE IF EXISTS `acl_rule`;
CREATE TABLE `acl_rule` (
  `id` int(11) NOT NULL auto_increment,
  `rank` bigint(10) unsigned NOT NULL,
  `deny` tinyint(1) NOT NULL default '0',
  `name` varchar(128) default NULL,
  `desc` text,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `acl_rule`
--

LOCK TABLES `acl_rule` WRITE;
/*!40000 ALTER TABLE `acl_rule` DISABLE KEYS */;
/*!40000 ALTER TABLE `acl_rule` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `acl_time_cross`
--

DROP TABLE IF EXISTS `acl_time_cross`;
CREATE TABLE `acl_time_cross` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `rule_id` int(10) unsigned NOT NULL,
  `acl_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `acl_time_cross`
--

LOCK TABLES `acl_time_cross` WRITE;
/*!40000 ALTER TABLE `acl_time_cross` DISABLE KEYS */;
/*!40000 ALTER TABLE `acl_time_cross` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `blacklist_category`
--

DROP TABLE IF EXISTS `blacklist_category`;
CREATE TABLE `blacklist_category` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `catid` int(10) unsigned NOT NULL,
  `group_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `blacklist_category`
--

LOCK TABLES `blacklist_category` WRITE;
/*!40000 ALTER TABLE `blacklist_category` DISABLE KEYS */;
/*!40000 ALTER TABLE `blacklist_category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
CREATE TABLE `category` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(128) NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `catname` USING HASH (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=85 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `content`
--

DROP TABLE IF EXISTS `content`;
CREATE TABLE `content` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `content` text NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `content`
--

LOCK TABLES `content` WRITE;
/*!40000 ALTER TABLE `content` DISABLE KEYS */;
/*!40000 ALTER TABLE `content` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `domain`
--

DROP TABLE IF EXISTS `domain`;
CREATE TABLE `domain` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `domain` varchar(128) NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `domain` USING HASH (`domain`)
) ENGINE=MyISAM AUTO_INCREMENT=1687879 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `domain`
--

LOCK TABLES `domain` WRITE;
/*!40000 ALTER TABLE `domain` DISABLE KEYS */;
/*!40000 ALTER TABLE `domain` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ip_table`
--

DROP TABLE IF EXISTS `ip_table`;
CREATE TABLE `ip_table` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(128) NOT NULL,
  `local_ip` bigint(20) NOT NULL,
  `local_mask` bigint(20) NOT NULL,
  `local_masked_ip` bigint(20) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ip_table`
--

LOCK TABLES `ip_table` WRITE;
/*!40000 ALTER TABLE `ip_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `ip_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mime_type`
--

DROP TABLE IF EXISTS `mime_type`;
CREATE TABLE `mime_type` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `file_ext` varchar(16) NOT NULL,
  `mime_type` varchar(128) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=645 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `mime_type`
--

LOCK TABLES `mime_type` WRITE;
/*!40000 ALTER TABLE `mime_type` DISABLE KEYS */;
/*!40000 ALTER TABLE `mime_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mime_type_cross`
--

DROP TABLE IF EXISTS `mime_type_cross`;
CREATE TABLE `mime_type_cross` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `mime_group_id` int(10) unsigned NOT NULL,
  `mime_type_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=37 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mime_type_cross`
--

LOCK TABLES `mime_type_cross` WRITE;
/*!40000 ALTER TABLE `mime_type_cross` DISABLE KEYS */;
/*!40000 ALTER TABLE `mime_type_cross` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mime_type_group`
--

DROP TABLE IF EXISTS `mime_type_group`;
CREATE TABLE `mime_type_group` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(128) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mime_type_group`
--

LOCK TABLES `mime_type_group` WRITE;
/*!40000 ALTER TABLE `mime_type_group` DISABLE KEYS */;
/*!40000 ALTER TABLE `mime_type_group` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `time_table`
--

DROP TABLE IF EXISTS `time_table`;
CREATE TABLE `time_table` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(128) NOT NULL,
  `start_time` time NOT NULL,
  `end_time` time NOT NULL,
  `day_of_week` tinyint(4) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=16 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `time_table`
--

LOCK TABLES `time_table` WRITE;
/*!40000 ALTER TABLE `time_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `time_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `url`
--

DROP TABLE IF EXISTS `url`;
CREATE TABLE `url` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `url` varchar(512) NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `url` USING HASH (`url`)
) ENGINE=MyISAM AUTO_INCREMENT=661040 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `url`
--

LOCK TABLES `url` WRITE;
/*!40000 ALTER TABLE `url` DISABLE KEYS */;
/*!40000 ALTER TABLE `url` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(128) NOT NULL,
  `password` varchar(64) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2009-03-31 20:31:54
