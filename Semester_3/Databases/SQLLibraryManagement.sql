CREATE TABLE Authors(
	id INT PRIMARY KEY IDENTITY(1,1),
	name VARCHAR(20) NOT NULL UNIQUE
)

CREATE TABLE Books(
	id INT PRIMARY KEY IDENTITY(1, 1),
	authorId INT NOT NULL,
	title VARCHAR(50) NOT NULL,
	genre VARCHAR(20) NOT NULL,
	publicationYear INT CHECK (publicationYear >= 2000)
	FOREIGN KEY (authorId) REFERENCES Authors(id) ON DELETE CASCADE
)

CREATE TABLE Members(
	id INT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(20) NOT NULL,
	startDate DATE NOT NULL CHECK (startDate <= GETDATE()),
	maximumAmountToRent INT DEFAULT 5
)

CREATE TABLE Rentals(
	bookId INT NOT NULL,
	memberId INT NOT NULL,
	rentalDate DATE NOT NULL,
	returnDate DATE
	PRIMARY KEY (bookId, memberId),
	FOREIGN KEY (bookId) REFERENCES Books(id),
	FOREIGN KEY (memberId) REFERENCES Members(id),
	CHECK (returnDate >= rentalDate AND DATEDIFF(DAY, rentalDate, returnDate) <= 30)
)

INSERT INTO Authors(name) VALUES ('Author2')
SELECT * FROM Authors

INSERT INTO Books(authorId, title, genre, publicationYear) VALUES (1, 'Book1', 'Fantasy', 2005)
SELECT * FROM Books

INSERT INTO Members(name, startDate) VALUES ('member1', '2024-10-01')
SELECT * FROM Members

INSERT INTO Rentals(bookId, memberId, rentalDate, returnDate) VALUES(2, 1, '2024-08-01', '2024-10-09')