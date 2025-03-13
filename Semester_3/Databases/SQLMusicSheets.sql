CREATE TABLE Composer(
	compId INT PRIMARY KEY IDENTITY(1, 1),
	compName VARCHAR(100) NOT NULL,
	birthDate DATE NOT NULL,
	deathDate DATE
);

CREATE TABLE PlatformUser(
	userId INT PRIMARY KEY IDENTITY(1, 1),
	username VARCHAR(50) NOT NULL,
	email VARCHAR(50) NOT NULL,
);

CREATE TABLE Instrument(
	instrId INT PRIMARY KEY IDENTITY(1, 1),
	instrName VARCHAR(50),	-- e.g., "Piano", "Guitar", "Drums"
	category VARCHAR(50)	-- e.g. "Keyboard", "Percussion", "Strings", "Wind"
);

CREATE TABLE Album(
	albumId INT PRIMARY KEY IDENTITY(1, 1),
	albumName VARCHAR(50),
	albumYear INT NOT NULL
);

CREATE TABLE License(
    licenseId INT PRIMARY KEY IDENTITY(1, 1),
    licenseType VARCHAR(50) NOT NULL, -- e.g., "Public Domain", "Creative Commons", "Copyright"
    description VARCHAR(255) -- More information about the license
);

CREATE TABLE MusicSheet(
	musicId INT PRIMARY KEY IDENTITY(1, 1),
	title VARCHAR(50) NOT NULL,
	genre VARCHAR(50),	-- e.g. "Classical", "Pop", "Rock"
	nrPurchases INT,	-- how many times a music sheet was acquired
	isFree BIT,			-- does the user need to pay for it
	license INT, -- Foreign key to License table
    FOREIGN KEY (license) REFERENCES License(licenseId)
);


CREATE TABLE Performance(
	performanceId INT PRIMARY KEY IDENTITY(1, 1),
    musicId INT NOT NULL,
    userId INT NOT NULL,
    performanceDate DATE NOT NULL,
    rating INT,
    reviewText VARCHAR(255),
    FOREIGN KEY (musicId) REFERENCES MusicSheet(musicId),
    FOREIGN KEY (userId) REFERENCES PlatformUser(userId)
);

CREATE TABLE MusicSheet_Instrument(
    musicId INT,
    instrId INT,
    PRIMARY KEY (musicId, instrId),
    FOREIGN KEY (musicId) REFERENCES MusicSheet(musicId),
    FOREIGN KEY (instrId) REFERENCES Instrument(instrId)
);

CREATE TABLE MusicSheet_Album(
    musicId INT,
    albumId INT,
    PRIMARY KEY (musicId, albumId),
    FOREIGN KEY (musicId) REFERENCES MusicSheet(musicId),
    FOREIGN KEY (albumId) REFERENCES Album(albumId)
);

CREATE TABLE Composer_MusicSheet(
    compId INT,
    musicId INT,
    PRIMARY KEY (compId, musicId),
    FOREIGN KEY (compId) REFERENCES Composer(compId),
    FOREIGN KEY (musicId) REFERENCES MusicSheet(musicId)
);