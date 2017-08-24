PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS samples;
DROP TABLE IF EXISTS devices;
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS tracks;

CREATE TABLE `samples` (
  `idSample` INTEGER NOT NULL,
  `idTrack` INTEGER NOT NULL,
  `timestamp` timestamp NOT NULL,
  `coordinates` TEXT NOT NULL,
  `speed` INTEGER NOT NULL,
  `acceleration` INTEGER  NOT NULL,
  `azimuth` INTEGER NOT NULL,
   PRIMARY KEY (idSample),
   FOREIGN KEY (idTrack) REFERENCES track(idTrack)
);

CREATE TABLE `devices` (
  `idDevice` INTEGER NOT NULL,
  `idUser`  INTEGER NOT NULL,
  `serialNumber` INTEGER NOT NULL,
  `currentLocation` TEXT NOT NULL,
  `deviceName` TEXT NULL,
  `programVersion` INTEGER DEFAULT NULL,
   PRIMARY KEY (idDevice),
   FOREIGN KEY (idUser) REFERENCES users(idUser)
);

CREATE TABLE `users` (
  `idUser` INTEGER NOT NULL,
  `userName` TEXT NOT NULL,
  `name` TEXT NOT NULL,
  `surname` TEXT  NOT NULL,
  `city` TEXT NOT NULL,
  `street` TEXT NOT NULL,
  `homeNumber` TEXT NOT NULL,
  `flatNumber` TEXT DEFAULT NULL,
  `postalCode` TEXT DEFAULT NULL,
  `passwordHash` TEXT NOT NULL,
   PRIMARY KEY (idUser)
);

CREATE TABLE `tracks` (
  `idTrack` INTEGER NOT NULL,
  `idDevice` INTEGER NOT NULL,
  `startDate` timestamp NOT NULL,
  `startLocation` TEXT  NOT NULL,
  `endDate` timestamp DEFAULT NULL,
  `endLocation` TEXT ,
  `distance` INTEGER ,
  `manouverAssessment` INTEGER, 
   PRIMARY KEY (idTrack),
   FOREIGN KEY (idDevice) REFERENCES devices(idDevice)
);
