-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: db
-- Erstellungszeit: 27. Mai 2024 um 14:34
-- Server-Version: 8.4.0
-- PHP-Version: 8.2.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Datenbank: `hrmgt_database`
--

DROP DATABASE IF EXISTS hrmgt_database;
CREATE DATABASE hrmgt_database;

use hrmgt_database;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `ABSENCE`
--

CREATE TABLE `ABSENCE` (
  `id` int NOT NULL,
  `employeeid` int DEFAULT NULL,
  `titel` varchar(255) NOT NULL,
  `absencestart` datetime DEFAULT NULL,
  `absenceend` datetime DEFAULT NULL,
  `absencereason` int NOT NULL,
  `note` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `status` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `ABSENCE_REASON`
--

CREATE TABLE `ABSENCE_REASON` (
  `id` int NOT NULL,
  `reason` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Daten für Tabelle `ABSENCE_REASON`
--

INSERT INTO `ABSENCE_REASON` (`id`, `reason`) VALUES
(1, 'Urlaub'),
(2, 'Zeitausgleich');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `ADDRESS`
--

CREATE TABLE `ADDRESS` (
  `id` int NOT NULL,
  `plz` int DEFAULT NULL,
  `city` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `street` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `housenumber` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Daten für Tabelle `ADDRESS`
--

INSERT INTO `ADDRESS` (`id`, `plz`, `city`, `street`, `housenumber`) VALUES
(1, 1010, 'Wien', 'Musterstraße', 13);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `DEPARTMENT`
--

CREATE TABLE `DEPARTMENT` (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `EMPLOYEE`
--

CREATE TABLE `EMPLOYEE` (
  `id` int NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `surname` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `mail` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `phone` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `employmentdate` date DEFAULT NULL,
  `terminationdate` date DEFAULT NULL,
  `adressid` int DEFAULT NULL,
  `departmentid` int DEFAULT NULL,
  `salaryid` int DEFAULT NULL,
  `admin` int DEFAULT '0',
  `gender` int NOT NULL,
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Daten für Tabelle `EMPLOYEE`
--

INSERT INTO `EMPLOYEE` (`password`, `name`, `surname`, `mail`, `phone`, `employmentdate`, `terminationdate`, `adressid`, `departmentid`, `salaryid`, `admin`, `gender`, `title`) VALUES
('d787a3c0317fd70de01da92b71d1808bf3d4ae75ff6693dae9289b5fe9997d24bf2f1d4810526b9f12ea38ffe7fd526b53811bf8b9df567c2ac9fa177a09b0d8', 'Flo', 'Mimmler', 'fmimmler@gmail.com', '+4367006070522', NULL, NULL, 1, NULL, NULL, 1, 1, 'Boss');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `SALARY`
--

CREATE TABLE `SALARY` (
  `id` int NOT NULL,
  `salary` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `GENDERS`
--

CREATE TABLE `GENDERS` (
  `id` int NOT NULL,
  `gender` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Daten für Tabelle `GENDERS`
--

INSERT INTO `GENDERS` (`id`, `gender`) VALUES
(1, 'Herr'),
(2, 'Frau'),
(3, 'Divers');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `WORKINGHOURS`
--

CREATE TABLE `WORKINGHOURS` (
  `id` int NOT NULL,
  `shiftstart` datetime DEFAULT NULL,
  `shiftend` datetime DEFAULT NULL,
  `employeeid` int DEFAULT NULL,
  `note` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `ACTIVE_EMPLOYEE`
--

CREATE TABLE `ACTIVE_EMPLOYEE` (
  `id` int NOT NULL,
  `employeeid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


--
-- Indizes der exportierten Tabellen
--

--
-- Indizes für die Tabelle `ABSENCE`
--
ALTER TABLE `ABSENCE`
  ADD PRIMARY KEY (`id`),
  ADD KEY `MitarbeiterID` (`employeeid`),
  ADD KEY `ABSENCE_REASON` (`absencereason`);

--
-- Indizes für die Tabelle `ABSENCE_REASON`
--
ALTER TABLE `ABSENCE_REASON`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `ADDRESS`
--
ALTER TABLE `ADDRESS`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `DEPARTMENT`
--
ALTER TABLE `DEPARTMENT`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `EMPLOYEE`
--
ALTER TABLE `EMPLOYEE`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `mail` (`mail`),
  ADD KEY `OrtID` (`adressid`),
  ADD KEY `AbteilungsID` (`departmentid`),
  ADD KEY `GehaltID` (`salaryid`),
  ADD KEY `gender` (`gender`);

--
-- Indizes für die Tabelle `SALARY`
--
ALTER TABLE `SALARY`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `GENDERS`
--
ALTER TABLE `GENDERS`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `WORKINGHOURS`
--
ALTER TABLE `WORKINGHOURS`
  ADD PRIMARY KEY (`id`),
  ADD KEY `MitarbeitderID` (`employeeid`);

--
-- Indizes für die Tabelle `ACTIVE_EMPLOYEE`
--
ALTER TABLE `ACTIVE_EMPLOYEE`
  ADD PRIMARY KEY (`id`),
  ADD KEY `MitarbeiterID` (`employeeid`);

--
-- AUTO_INCREMENT für exportierte Tabellen
--

--
-- AUTO_INCREMENT für Tabelle `ABSENCE`
--
ALTER TABLE `ABSENCE`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT für Tabelle `ABSENCE_REASON`
--
ALTER TABLE `ABSENCE_REASON`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

--
-- AUTO_INCREMENT für Tabelle `ADDRESS`
--
ALTER TABLE `ADDRESS`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT für Tabelle `DEPARTMENT`
--
ALTER TABLE `DEPARTMENT`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT für Tabelle `EMPLOYEE`
--
ALTER TABLE `EMPLOYEE`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;

--
-- AUTO_INCREMENT für Tabelle `SALARY`
--
ALTER TABLE `SALARY`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT für Tabelle `GENDERS`
--
ALTER TABLE `GENDERS`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT für Tabelle `WORKINGHOURS`
--
ALTER TABLE `WORKINGHOURS`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

ALTER TABLE `ACTIVE_EMPLOYEE`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- Constraints der exportierten Tabellen
--

--
-- Constraints der Tabelle `ABSENCE`
--
ALTER TABLE `ABSENCE`
  ADD CONSTRAINT `ABSENCE_ibfk_1` FOREIGN KEY (`employeeid`) REFERENCES `EMPLOYEE` (`id`),
  ADD CONSTRAINT `ABSENCE_REASON` FOREIGN KEY (`absencereason`) REFERENCES `ABSENCE_REASON` (`id`);
COMMIT;

--
-- Constraints der Tabelle `EMPLOYEE`
--
ALTER TABLE `EMPLOYEE`
  ADD CONSTRAINT `EMPLOYEE_ibfk_1` FOREIGN KEY (`adressid`) REFERENCES `ADDRESS` (`id`),
  ADD CONSTRAINT `EMPLOYEE_ibfk_2` FOREIGN KEY (`departmentid`) REFERENCES `DEPARTMENT` (`id`),
  ADD CONSTRAINT `EMPLOYEE_ibfk_3` FOREIGN KEY (`salaryid`) REFERENCES `SALARY` (`id`),
  ADD CONSTRAINT `EMPLOYEE_ibfk_4` FOREIGN KEY (`gender`) REFERENCES `GENDERS` (`id`);

--
-- Constraints der Tabelle `WORKINGHOURS`
--
ALTER TABLE `WORKINGHOURS`
  ADD CONSTRAINT `WORKINGHOURS_ibfk_1` FOREIGN KEY (`employeeid`) REFERENCES `EMPLOYEE` (`id`);
COMMIT;

--
-- Constraints der Tabelle `ACTIVE_EMPLOYEE`
--
ALTER TABLE `ACTIVE_EMPLOYEE`
  ADD CONSTRAINT `MitarbeiterID` FOREIGN KEY (`employeeid`) REFERENCES `EMPLOYEE` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
