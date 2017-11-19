PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS samples;
DROP TABLE IF EXISTS devices;
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS tracks;

CREATE TABLE `users`(
  `idUser` INTEGER PRIMARY KEY AUTOINCREMENT,
  `userName` TEXT NOT NULL,
  `name` TEXT NOT NULL,
  `surname` TEXT  NOT NULL,
  `email` TEXT NOT NULL,
  `telephone` INTEGER DEFAULT NULL,
  `city` TEXT NOT NULL,
  `street` TEXT NOT NULL,
  `homeNumber` TEXT NOT NULL,
  `flatNumber` TEXT DEFAULT NULL,
  `postalCode` TEXT DEFAULT NULL,
  `passwordHash` TEXT NOT NULL
);

CREATE TABLE `devices`(
  `idDevice` INTEGER PRIMARY KEY AUTOINCREMENT,
  `idUser`  INTEGER NOT NULL,
  `serialNumber` INTEGER NOT NULL,
  `phoneNumber` INTEGER NOT NULL,
  `currentLocation` TEXT NOT NULL,
  `deviceName` TEXT NULL,
  `firmwareVersion` TEXT DEFAULT "1.0",
   FOREIGN KEY (idUser) REFERENCES users(idUser)
);

CREATE TABLE `tracks`(
  `idTrack` INTEGER PRIMARY KEY AUTOINCREMENT,
  `idDevice` INTEGER NOT NULL,
  `startDate` timestamp NOT NULL,
  `startLocation` TEXT  NOT NULL,
  `endDate` timestamp DEFAULT NULL,
  `endLocation` TEXT ,
  `distance` INTEGER ,
  `trackAssessment` INTEGER, 
   FOREIGN KEY (idDevice) REFERENCES devices(idDevice)
);

CREATE TABLE `samples`(
  `idSample` INTEGER PRIMARY KEY AUTOINCREMENT,
  `idTrack` INTEGER NOT NULL,
  `timestamp` timestamp NOT NULL,
  `coordinates` TEXT NOT NULL,
  `speed` INTEGER NOT NULL,
  `acceleration` INTEGER  NOT NULL,
  `azimuth` INTEGER NOT NULL,
  `numOfSats` INTEGER NOT NULL,
  `hdop` INTEGER NOT NULL,
  `manouverAssessment` INTEGER NOT NULL,
   FOREIGN KEY (idTrack) REFERENCES tracks(idTrack)
);


