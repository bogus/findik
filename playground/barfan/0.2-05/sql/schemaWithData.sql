-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Feb 21, 2009 at 01:55 AM
-- Server version: 5.0.45
-- PHP Version: 5.1.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `findik`
--

-- --------------------------------------------------------

--
-- Table structure for table `blacklist_content`
--

CREATE TABLE IF NOT EXISTS `blacklist_content` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `content` varchar(333) default NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `content` USING HASH (`content`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `blacklist_content`
--

INSERT INTO `blacklist_content` (`id`, `content`, `rank`, `catid`) VALUES
(3, '(adultsight|adultsite|adultsonly|adultweb|blowjob|bondage|centerfold|cumshot|cyberlust|cybercore|hardcore|incest|masturbat|obscene|pedophil|pedofil|playmate|pornstar|sexdream|softcore|striptease)', 1, 1),
(4, 'qweasdzxcrtydfgc', 1, 2);

-- --------------------------------------------------------

--
-- Table structure for table `blacklist_domain`
--

CREATE TABLE IF NOT EXISTS `blacklist_domain` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `domain` varchar(128) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `domain` USING HASH (`domain`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `blacklist_domain`
--

INSERT INTO `blacklist_domain` (`id`, `domain`, `rank`, `catid`) VALUES
(1, 'www.live.com', 1, 1),
(2, 'www.asd.com', 1, 1);

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

--
-- Dumping data for table `blacklist_mime`
--

INSERT INTO `blacklist_mime` (`id`, `file_ext`, `mime_type`) VALUES
(1, 'swf', 'application/x-shockwave-flash'),
(2, 'gz', 'application/x-gzip');

-- --------------------------------------------------------

--
-- Table structure for table `blacklist_url`
--

CREATE TABLE IF NOT EXISTS `blacklist_url` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `url` varchar(512) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `url` USING HASH (`url`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `blacklist_url`
--

INSERT INTO `blacklist_url` (`id`, `url`, `rank`, `catid`) VALUES
(1, 'http://www.linuxquestions.org/questions/linux-server-73/centos-5-apache-php-mysql-623173/', 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `category`
--

CREATE TABLE IF NOT EXISTS `category` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `catname` varchar(128) NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `catname` USING HASH (`catname`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `category`
--

INSERT INTO `category` (`id`, `catname`) VALUES
(1, 'search engine'),
(2, 'burak1');

-- --------------------------------------------------------

--
-- Table structure for table `whitelist_content`
--

CREATE TABLE IF NOT EXISTS `whitelist_content` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `content` varchar(128) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `content` USING HASH (`content`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `whitelist_content`
--


-- --------------------------------------------------------

--
-- Table structure for table `whitelist_domain`
--

CREATE TABLE IF NOT EXISTS `whitelist_domain` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `domain` varchar(128) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `domain` USING HASH (`domain`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `whitelist_domain`
--


-- --------------------------------------------------------

--
-- Table structure for table `whitelist_url`
--

CREATE TABLE IF NOT EXISTS `whitelist_url` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `url` varchar(512) NOT NULL,
  `rank` int(10) unsigned NOT NULL,
  `catid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `url` USING HASH (`url`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `whitelist_url`
--


