use test;
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `user` varchar(20) DEFAULT NULL,
  `pass` varchar(20) DEFAULT NULL,
  `data3` varchar(20) DEFAULT NULL,
  `data4` varchar(20) DEFAULT NULL,
  `data5` varchar(20) DEFAULT NULL,
  `data6` varchar(20) DEFAULT NULL,
  `data7` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

LOCK TABLES `users` WRITE;
INSERT INTO `users` VALUES (1,'Jonathan Prado','jprado','jpradoPass',NULL,NULL,NULL,NULL,NULL),(2,'Viewer','guest','guest',NULL,NULL,NULL,NULL,NULL);
UNLOCK TABLES;
