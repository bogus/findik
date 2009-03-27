-- MySQL Dump

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `findik`
--

-- --------------------------------------------------------

--
-- Table structure for table `acl_filter_param`
--

CREATE TABLE IF NOT EXISTS `acl_filter_param` (
  `id` int(11) NOT NULL auto_increment,
  `rule_id` int(11) NOT NULL,
  `filter_key` varchar(32) NOT NULL,
  `param` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `rule_id` (`rule_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `acl_match_ip`
--

CREATE TABLE IF NOT EXISTS `acl_match_ip` (
  `id` int(11) NOT NULL auto_increment,
  `rule_id` int(11) NOT NULL,
  `local_ip` bigint(20) unsigned NOT NULL default '0',
  `local_mask` bigint(20) unsigned NOT NULL default '0',
  `local_masked_ip` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `local_masked_ip` (`local_masked_ip`),
  KEY `rule_id` (`rule_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `acl_match_time`
--

CREATE TABLE IF NOT EXISTS `acl_match_time` (
  `id` int(11) NOT NULL auto_increment,
  `rule_id` int(11) NOT NULL,
  `start` time NOT NULL default '00:00:00',
  `end` time NOT NULL default '23:59:59',
  `day_of_week` tinyint(3) unsigned NOT NULL default '254',
  PRIMARY KEY  (`id`),
  KEY `start` (`start`),
  KEY `end` (`end`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `acl_rule`
--

CREATE TABLE IF NOT EXISTS `acl_rule` (
  `id` int(11) NOT NULL auto_increment,
  `deny` tinyint(1) NOT NULL default '0',
  `name` varchar(128) default NULL,
  `desc` text,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `blacklist_category`
--

CREATE TABLE IF NOT EXISTS `blacklist_category` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `catid` int(10) unsigned NOT NULL,
  `group_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

-- --------------------------------------------------------

--
-- Table structure for table `blacklist_mime`
--

CREATE TABLE IF NOT EXISTS `blacklist_mime` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `file_ext` varchar(16) NOT NULL,
  `mime_type` varchar(128) NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `file_ext` USING HASH (`file_ext`),
  UNIQUE KEY `mime_type` USING HASH (`mime_type`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

-- --------------------------------------------------------

--
-- Table structure for table `category`
--

CREATE TABLE IF NOT EXISTS `category` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `catname` varchar(128) NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `catname` USING HASH (`catname`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=85 ;

-- --------------------------------------------------------

--
-- Table structure for table `content`
--

CREATE TABLE IF NOT EXISTS `content` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `content` text NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

-- --------------------------------------------------------

--
-- Table structure for table `domain`
--

CREATE TABLE IF NOT EXISTS `domain` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `domain` varchar(128) NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `domain` USING HASH (`domain`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1687878 ;

-- --------------------------------------------------------

--
-- Table structure for table `url`
--

CREATE TABLE IF NOT EXISTS `url` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `url` varchar(512) NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `url` USING HASH (`url`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=661038 ;

