CREATE TABLE `Mitarbeiter` (
  `MitarbeiterID` integer PRIMARY KEY AUTO_INCREMENT,
  `Passwort` varchar(255),
  `Vorname` varchar(255),
  `Nachname` varchar(255),
  `Email` varchar(255),
  `Telefonnummer` varchar(255),
  `Anstellungsdatum` date,
  `Kuendigungsdatum` date,
  `OrtID` integer,
  `AbteilungsID` integer,
  `GehaltID` integer
);

CREATE TABLE `Ort` (
  `OrtID` integer PRIMARY KEY AUTO_INCREMENT,
  `Plz` integer,
  `Bundesland` varchar(255),
  `Strasse` varchar(255),
  `Hausnummer` integer
);

CREATE TABLE `Abteilung` (
  `AbteilungsID` integer PRIMARY KEY AUTO_INCREMENT,
  `Abteilungsname` varchar(255)
);

CREATE TABLE `Gehalt` (
  `GehaltID` integer PRIMARY KEY AUTO_INCREMENT,
  `Monatsgehalt` float
);

CREATE TABLE `Arbeitszeiten` (
  `ArbeitszeitenID` integer PRIMARY KEY AUTO_INCREMENT,
  `Arbeitsbeginn` date,
  `Arbeitsende` date,
  `MitarbeitderID` integer,
  `Notiz` text
);

CREATE TABLE `Abweseneinheit` (
  `AbwesenheitsID` integer PRIMARY KEY AUTO_INCREMENT,
  `MitarbeiterID` integer,
  `Abwesenheitsbeginn` date,
  `Abwesenheitsende` date,
  `Abwesenheitsgrund` varchar(255),
  `Notiz` varchar(255),
  `Stauts` varchar(255)
);

ALTER TABLE `Mitarbeiter` ADD FOREIGN KEY (`OrtID`) REFERENCES `Ort` (`OrtID`);

ALTER TABLE `Mitarbeiter` ADD FOREIGN KEY (`AbteilungsID`) REFERENCES `Abteilung` (`AbteilungsID`);

ALTER TABLE `Mitarbeiter` ADD FOREIGN KEY (`GehaltID`) REFERENCES `Gehalt` (`GehaltID`);

ALTER TABLE `Arbeitszeiten` ADD FOREIGN KEY (`MitarbeitderID`) REFERENCES `Mitarbeiter` (`MitarbeiterID`);

ALTER TABLE `Abweseneinheit` ADD FOREIGN KEY (`MitarbeiterID`) REFERENCES `Mitarbeiter` (`MitarbeiterID`);
