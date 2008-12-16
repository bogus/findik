-- phpMyAdmin SQL Dump
-- version 3.0.1.1
-- http://www.phpmyadmin.net
--
-- Anamakine: localhost
-- �retim Zaman�: 14 Aral�k 2008 saat 17:57:24
-- Sunucu s�r�m�: 5.1.30
-- PHP S�r�m�: 5.2.7

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Veritaban�: `findik`
--

-- --------------------------------------------------------

--
-- Tablo yap�s�: `blacklist_content`
--

CREATE TABLE `blacklist_content` (
`id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
`content` varchar(128) NOT NULL,
`rank` int(10) unsigned NOT NULL,
`catid` int(10) unsigned NOT NULL,
PRIMARY KEY (`id`),
UNIQUE KEY `id` (`id`),
KEY `content` (`content`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Tablo d�k�m verisi `blacklist_content`
--


-- --------------------------------------------------------

--
-- Tablo yap�s�: `blacklist_domain`
--

CREATE TABLE `blacklist_domain` (
`id` int(10) unsigned NOT NULL AUTO_INCREMENT,
`domain` varchar(128) NOT NULL,
`rank` int(10) unsigned NOT NULL,
`catid` int(10) unsigned NOT NULL,
PRIMARY KEY (`id`),
UNIQUE KEY `id` (`id`),
KEY `domain` (`domain`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Tablo d�k�m verisi `blacklist_domain`
--

INSERT INTO `blacklist_domain` (`id`, `domain`, `rank`, `catid`) VALUES
(1, 'www.google.com.tr', 1, 1);

-- --------------------------------------------------------

--
-- Tablo yap�s�: `blacklist_url`
--

CREATE TABLE `blacklist_url` (
`id` int(10) unsigned NOT NULL AUTO_INCREMENT,
`url` varchar(512) NOT NULL,
`rank` int(10) unsigned NOT NULL,
`catid` int(10) unsigned NOT NULL,
PRIMARY KEY (`id`),
UNIQUE KEY `id` (`id`),
KEY `url` (`url`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Tablo d�k�m verisi `blacklist_url`
--


-- --------------------------------------------------------

--
-- Tablo yap�s�: `category`
--

CREATE TABLE `category` (
`id` int(10) unsigned NOT NULL AUTO_INCREMENT,
`catname` varchar(128) NOT NULL,
PRIMARY KEY (`id`),
UNIQUE KEY `id` (`id`),
KEY `catname` (`catname`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Tablo d�k�m verisi `category`
--

INSERT INTO `category` (`id`, `catname`) VALUES
(1, 'search engine');

-- --------------------------------------------------------

--
-- Tablo yap�s�: `whitelist_content`
--

CREATE TABLE `whitelist_content` (
`id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
`content` varchar(128) NOT NULL,
`rank` int(10) unsigned NOT NULL,
`catid` int(10) unsigned NOT NULL,
PRIMARY KEY (`id`),
UNIQUE KEY `id` (`id`),
KEY `content` (`content`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Tablo d�k�m verisi `whitelist_content`
--


-- --------------------------------------------------------

--
-- Tablo yap�s�: `whitelist_domain`
--

CREATE TABLE `whitelist_domain` (
`id` int(10) unsigned NOT NULL AUTO_INCREMENT,
`domain` varchar(128) NOT NULL,
`rank` int(10) unsigned NOT NULL,
`catid` int(10) unsigned NOT NULL,
PRIMARY KEY (`id`),
UNIQUE KEY `id` (`id`),
KEY `domain` (`domain`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Tablo d�k�m verisi `whitelist_domain`
--


-- --------------------------------------------------------

--
-- Tablo yap�s�: `whitelist_url`
--

CREATE TABLE `whitelist_url` (
`id` int(10) unsigned NOT NULL AUTO_INCREMENT,
`url` varchar(512) NOT NULL,
`rank` int(10) unsigned NOT NULL,
`catid` int(10) unsigned NOT NULL,
PRIMARY KEY (`id`),
UNIQUE KEY `id` (`id`),
KEY `url` (`url`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Tablo d�k�m verisi `whitelist_url`
--
