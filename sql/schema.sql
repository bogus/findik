-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 18, 2009 at 09:40 PM
-- Server version: 5.0.45
-- PHP Version: 5.1.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `findik`
--

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

