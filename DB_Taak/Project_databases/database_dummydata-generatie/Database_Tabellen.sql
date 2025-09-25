-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Gegenereerd op: 29 mei 2024 om 23:22
-- Serverversie: 10.4.32-MariaDB
-- PHP-versie: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `project_databases`
--

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `deelnames`
--

CREATE TABLE `deelnames` (
  `speler_id` bigint(11) NOT NULL,
  `match_id` bigint(11) NOT NULL,
  `score` int(8) NOT NULL DEFAULT 0,
  `vrijstelling` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `inschrijvingen`
--

CREATE TABLE `inschrijvingen` (
  `speler_id` bigint(11) NOT NULL,
  `reeks_id` bigint(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `matchen`
--

CREATE TABLE `matchen` (
  `id` bigint(11) NOT NULL,
  `ronde` int(7) NOT NULL,
  `reeks_id` bigint(11) NOT NULL,
  `scheidsrechter_id` bigint(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `reeksen`
--

CREATE TABLE `reeksen` (
  `leeftijdsgroep` enum('5-10','11-17','18+') NOT NULL,
  `geslacht` enum('man','vrouw') NOT NULL,
  `id` bigint(11) NOT NULL,
  `toernooi_id` bigint(11) NOT NULL,
  `gespeeld` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `spelers`
--

CREATE TABLE `spelers` (
  `id` bigint(11) NOT NULL,
  `nummer` int(11) NOT NULL,
  `hoogste ranking` int(11) NOT NULL DEFAULT 0,
  `persoonlijk_naam` varchar(20) NOT NULL,
  `persoonlijk_email` varchar(40) NOT NULL,
  `fysiek_geslacht` enum('man','vrouw') NOT NULL,
  `fysiek_leeftijd` int(7) NOT NULL,
  `tennisclub_id` bigint(11) NOT NULL,
  `aantal gespeelde matches` int(11) NOT NULL DEFAULT 0,
  `aantal gewonnen matches` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `tennisclubs`
--

CREATE TABLE `tennisclubs` (
  `id` bigint(11) NOT NULL,
  `naam` varchar(40) NOT NULL,
  `locatie` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `toernoois`
--

CREATE TABLE `toernoois` (
  `datum` date NOT NULL,
  `id` bigint(11) NOT NULL,
  `tennisclub_id` bigint(11) NOT NULL,
  `wedstrijdleider_id` bigint(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indexen voor geëxporteerde tabellen
--

--
-- Indexen voor tabel `matchen`
--
ALTER TABLE `matchen`
  ADD PRIMARY KEY (`id`);

--
-- Indexen voor tabel `reeksen`
--
ALTER TABLE `reeksen`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `UNIQUE leeftijdsgroep met geslacht met toernooi` (`leeftijdsgroep`,`geslacht`,`toernooi_id`) USING BTREE,
  ADD KEY `INDEX toernooi (key)` (`toernooi_id`) USING BTREE;

--
-- Indexen voor tabel `spelers`
--
ALTER TABLE `spelers`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `UNIQUE nummer met tennisclub` (`nummer`,`tennisclub_id`) USING BTREE,
  ADD KEY `INDEX tennisclub (key)` (`tennisclub_id`) USING BTREE;

--
-- Indexen voor tabel `tennisclubs`
--
ALTER TABLE `tennisclubs`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `UNIQUE naam met locatie` (`naam`,`locatie`) USING BTREE;

--
-- Indexen voor tabel `toernoois`
--
ALTER TABLE `toernoois`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY ` UNIQUE datum met tennisclub` (`datum`,`tennisclub_id`) USING BTREE,
  ADD KEY `INDEX tennisclub (key)` (`tennisclub_id`) USING BTREE;

--
-- AUTO_INCREMENT voor geëxporteerde tabellen
--

--
-- AUTO_INCREMENT voor een tabel `matchen`
--
ALTER TABLE `matchen`
  MODIFY `id` bigint(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `reeksen`
--
ALTER TABLE `reeksen`
  MODIFY `id` bigint(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `spelers`
--
ALTER TABLE `spelers`
  MODIFY `id` bigint(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `tennisclubs`
--
ALTER TABLE `tennisclubs`
  MODIFY `id` bigint(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `toernoois`
--
ALTER TABLE `toernoois`
  MODIFY `id` bigint(11) NOT NULL AUTO_INCREMENT;

--
-- Beperkingen voor geëxporteerde tabellen
--

--
-- Beperkingen voor tabel `reeksen`
--
ALTER TABLE `reeksen`
  ADD CONSTRAINT `deel van` FOREIGN KEY (`toernooi_id`) REFERENCES `toernoois` (`id`);

--
-- Beperkingen voor tabel `spelers`
--
ALTER TABLE `spelers`
  ADD CONSTRAINT `Zit in` FOREIGN KEY (`tennisclub_id`) REFERENCES `tennisclubs` (`id`);

--
-- Beperkingen voor tabel `toernoois`
--
ALTER TABLE `toernoois`
  ADD CONSTRAINT `Vind plaats` FOREIGN KEY (`tennisclub_id`) REFERENCES `tennisclubs` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
