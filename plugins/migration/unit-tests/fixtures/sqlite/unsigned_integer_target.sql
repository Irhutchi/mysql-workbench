CREATE  TABLE IF NOT EXISTS `UnsignedIntegerContainer` (
  `id` INT NULL DEFAULT NULL ,
  `tint` TINYINT UNSIGNED NULL DEFAULT NULL ,
  `sint` SMALLINT UNSIGNED NULL DEFAULT NULL ,
  `mint` MEDIUMINT UNSIGNED NULL DEFAULT NULL ,
  `iint` INT UNSIGNED NULL DEFAULT NULL ,
  `bint` BIGINT UNSIGNED NULL DEFAULT NULL ,
  PRIMARY KEY (`id`) );
