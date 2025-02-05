-- MySQL dump 10.13  Distrib 8.0.41, for Linux (x86_64)
--
-- Host: localhost    Database: Imobiliaria
-- ------------------------------------------------------
-- Server version	8.0.41-0ubuntu0.24.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `certidoes_imoveis`
--

DROP TABLE IF EXISTS `certidoes_imoveis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `certidoes_imoveis` (
  `id` char(36) NOT NULL,
  `id_prop` char(36) NOT NULL,
  `id_imovel` char(36) NOT NULL,
  `num_registro` char(36) NOT NULL,
  `data_registro` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_prop` (`id_prop`),
  KEY `id_imovel` (`id_imovel`),
  CONSTRAINT `certidoes_imoveis_ibfk_1` FOREIGN KEY (`id_prop`) REFERENCES `proprietarios` (`id`) ON DELETE CASCADE,
  CONSTRAINT `certidoes_imoveis_ibfk_2` FOREIGN KEY (`id_imovel`) REFERENCES `imoveis` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `contratos_alugueis`
--

DROP TABLE IF EXISTS `contratos_alugueis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `contratos_alugueis` (
  `id` char(36) NOT NULL,
  `id_inquilino` char(36) DEFAULT NULL,
  `id_imovel` char(36) DEFAULT NULL,
  `num_contrato` char(36) DEFAULT NULL,
  `valor` float DEFAULT NULL,
  `duracao` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `num_contrato` (`num_contrato`),
  KEY `id_inquilino` (`id_inquilino`),
  KEY `id_imovel` (`id_imovel`),
  CONSTRAINT `contratos_alugueis_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `inquilinos` (`id`) ON DELETE SET NULL,
  CONSTRAINT `contratos_alugueis_ibfk_2` FOREIGN KEY (`id_imovel`) REFERENCES `imoveis` (`id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `corretores_autonomos`
--

DROP TABLE IF EXISTS `corretores_autonomos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `corretores_autonomos` (
  `id` char(36) NOT NULL,
  `creci` char(36) DEFAULT NULL,
  `nome` varchar(255) DEFAULT NULL,
  `data_inicio` datetime DEFAULT NULL,
  `comissao` float DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `creci` (`creci`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `fiadores`
--

DROP TABLE IF EXISTS `fiadores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `fiadores` (
  `id` char(36) NOT NULL,
  `id_inq` char(36) NOT NULL,
  `cpf` varchar(14) DEFAULT NULL,
  `nome` varchar(255) DEFAULT NULL,
  `saldo` float DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `cpf` (`cpf`),
  KEY `id_inq` (`id_inq`),
  CONSTRAINT `fiadores_ibfk_1` FOREIGN KEY (`id_inq`) REFERENCES `inquilinos` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `imoveis`
--

DROP TABLE IF EXISTS `imoveis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `imoveis` (
  `id` char(36) NOT NULL,
  `cep` varchar(8) DEFAULT NULL,
  `cidade` varchar(100) DEFAULT NULL,
  `bairro` varchar(100) DEFAULT NULL,
  `rua` varchar(100) DEFAULT NULL,
  `complemento` varchar(100) DEFAULT NULL,
  `num_comodos` int DEFAULT NULL,
  `num_vagas` int DEFAULT NULL,
  `area_construida` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `inquilinos`
--

DROP TABLE IF EXISTS `inquilinos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `inquilinos` (
  `id` char(36) NOT NULL,
  `cpf` varchar(14) DEFAULT NULL,
  `nome` varchar(255) DEFAULT NULL,
  `profissao` varchar(50) DEFAULT NULL,
  `renda_familiar` float DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `cpf` (`cpf`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ofertas`
--

DROP TABLE IF EXISTS `ofertas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ofertas` (
  `id` char(36) NOT NULL,
  `id_prop` char(36) NOT NULL,
  `id_imovel` char(36) NOT NULL,
  `id_corretor` char(36) DEFAULT NULL,
  `valor_desejado` float DEFAULT NULL,
  `data` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_prop` (`id_prop`),
  KEY `id_imovel` (`id_imovel`),
  KEY `id_corretor` (`id_corretor`),
  CONSTRAINT `ofertas_ibfk_1` FOREIGN KEY (`id_prop`) REFERENCES `proprietarios` (`id`) ON DELETE CASCADE,
  CONSTRAINT `ofertas_ibfk_2` FOREIGN KEY (`id_imovel`) REFERENCES `imoveis` (`id`) ON DELETE CASCADE,
  CONSTRAINT `ofertas_ibfk_3` FOREIGN KEY (`id_corretor`) REFERENCES `corretores_autonomos` (`id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `propostas`
--

DROP TABLE IF EXISTS `propostas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `propostas` (
  `id` char(36) NOT NULL,
  `id_inquilino` char(36) DEFAULT NULL,
  `id_imovel` char(36) DEFAULT NULL,
  `valor` float DEFAULT NULL,
  `validade` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_inquilino` (`id_inquilino`),
  KEY `id_imovel` (`id_imovel`),
  CONSTRAINT `propostas_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `inquilinos` (`id`) ON DELETE SET NULL,
  CONSTRAINT `propostas_ibfk_2` FOREIGN KEY (`id_imovel`) REFERENCES `imoveis` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `proprietarios`
--

DROP TABLE IF EXISTS `proprietarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proprietarios` (
  `id` char(36) NOT NULL,
  `cpf` varchar(14) DEFAULT NULL,
  `nome` varchar(255) DEFAULT NULL,
  `estado_civil` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `cpf` (`cpf`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `telefones_corretores_autonomos`
--

DROP TABLE IF EXISTS `telefones_corretores_autonomos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `telefones_corretores_autonomos` (
  `id` char(36) NOT NULL,
  `numero` varchar(30) DEFAULT NULL,
  `id_corretor` char(36) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `numero` (`numero`),
  KEY `id_corretor` (`id_corretor`),
  CONSTRAINT `telefones_corretores_autonomos_ibfk_1` FOREIGN KEY (`id_corretor`) REFERENCES `corretores_autonomos` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `telefones_fiadores`
--

DROP TABLE IF EXISTS `telefones_fiadores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `telefones_fiadores` (
  `id` char(36) NOT NULL,
  `numero` varchar(30) DEFAULT NULL,
  `id_fiador` char(36) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `numero` (`numero`),
  KEY `id_fiador` (`id_fiador`),
  CONSTRAINT `telefones_fiadores_ibfk_1` FOREIGN KEY (`id_fiador`) REFERENCES `fiadores` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `telefones_inquilinos`
--

DROP TABLE IF EXISTS `telefones_inquilinos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `telefones_inquilinos` (
  `id` char(36) NOT NULL,
  `numero` varchar(30) DEFAULT NULL,
  `id_inquilino` char(36) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `numero` (`numero`),
  KEY `id_inquilino` (`id_inquilino`),
  CONSTRAINT `telefones_inquilinos_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `inquilinos` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `telefones_proprietarios`
--

DROP TABLE IF EXISTS `telefones_proprietarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `telefones_proprietarios` (
  `id` char(36) NOT NULL,
  `numero` varchar(30) DEFAULT NULL,
  `id_proprietario` char(36) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `numero` (`numero`),
  KEY `id_proprietario` (`id_proprietario`),
  CONSTRAINT `telefones_proprietarios_ibfk_1` FOREIGN KEY (`id_proprietario`) REFERENCES `proprietarios` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `visitas`
--

DROP TABLE IF EXISTS `visitas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `visitas` (
  `id` char(36) NOT NULL,
  `id_inquilino` char(36) DEFAULT NULL,
  `id_imovel` char(36) DEFAULT NULL,
  `id_corretor` char(36) DEFAULT NULL,
  `data` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_inquilino` (`id_inquilino`),
  KEY `id_imovel` (`id_imovel`),
  KEY `id_corretor` (`id_corretor`),
  CONSTRAINT `visitas_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `inquilinos` (`id`) ON DELETE SET NULL,
  CONSTRAINT `visitas_ibfk_2` FOREIGN KEY (`id_imovel`) REFERENCES `imoveis` (`id`) ON DELETE CASCADE,
  CONSTRAINT `visitas_ibfk_3` FOREIGN KEY (`id_corretor`) REFERENCES `corretores_autonomos` (`id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-02-04 23:44:09
