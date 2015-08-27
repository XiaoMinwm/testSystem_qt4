drop database if exists mydb; 
create database mydb;   

use mydb;  

CREATE TABLE `Usr` (
     `ID` int(11) NOT NULL,
     `Name` varchar(20) DEFAULT 'root',
     `PassWd` varchar(20) DEFAULT '878455',
     `Type` varchar(20) DEFAULT NULL,
     PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

CREATE TABLE `Teacher` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `ThNum` char(20) NOT NULL,
  `Name` char(20) DEFAULT NULL,
  `PassWd` char(20) DEFAULT NULL,
  PRIMARY KEY (`ID`,`ThNum`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

CREATE TABLE `Student` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `StdNum` char(20) NOT NULL,
  `Name` char(20) DEFAULT NULL,
  `PassWd` char(20) DEFAULT NULL,
  PRIMARY KEY (`ID`,`StdNum`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

CREATE TABLE `Question` (
  `ID` int(11) NOT NULL,
  `Sub` char(40) NOT NULL,
  `Title` char(40) NOT NULL,
  `Content` char(255) NOT NULL,
  `Ans` char(2) NOT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

CREATE TABLE `Score` (
  `ID` int(11) NOT NULL,
  `StdNum` varchar(20) DEFAULT NULL,
  `Sub` varchar(20) DEFAULT NULL,
  `Score` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
