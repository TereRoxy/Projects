-- Add entries in the tables

-- Attempting to insert a music sheet with an invalid license ID (99), violating referential integrity
-- This error demonstrates that the license ID must exist in the License table.
INSERT INTO MusicSheet (title, genre, nrPurchases, isFree, license) VALUES
    ('Symphony No. 5', 'Classical', 150, 1, 99);

INSERT INTO Composer(compName, birthDate, deathDate) VALUES
	('Ludwig van Beethoven', '1770-12-17', '1827-03-26'),
	('Frederic Chopin', '1810-03-01', '1849-10-17'),
	('Johann Strauss', '1825-10-25', '1899-06-03'),
	('Franz Joseph Haydn', '1732-03-31', '1809-05-31'),
	('Dmitri Shostakovich', '1906-09-12', '1975-08-09');

INSERT INTO Instrument(instrName, category) VALUES
	('Piano', 'Keyboard'),
	('Drums', 'Percussion'),
	('Violin', 'Strings'),
	('Kazoo', ''),
	('Guitar', 'Strings');

INSERT INTO PlatformUser(username, email) VALUES
	('popjohn', 'popjohn@gmail.com'),
	('musiclover', 'musiclover123@gmail.com'),
	('notfounder', 'notfounder404@gmail.com'),
	('pianoteacher', 'pianoteacher314@gmail.com');

INSERT INTO License(licenseType, description) VALUES
	('Public Domain', 'It is free to use by anyone'),
	('Creative Commons', 'It has some restrictions for use'),
	('Copyright', 'It protects intellectual property');

INSERT INTO Album (albumName, albumYear) VALUES
    ('Beethoven Complete Symphonies', 2005),
    ('Mozart: The Complete Piano Sonatas', 2009),
    ('The Best of Bach', 2012),
    ('Vivaldi: Four Seasons and Other Concertos', 2015),
    ('Greatest Classical Hits', 2018),
    ('Romantic Piano Classics', 2020),
    ('Jazz for the Soul', 2019),
    ('Ultimate Guitar Anthems', 2021),
    ('Chopin: Nocturnes', 2010),
    ('Classical Moods for Study', 2017);

INSERT INTO MusicSheet (title, genre, nrPurchases, isFree, license) VALUES
    ('Symphony No. 5', 'Classical', 500, 0, 1),        -- Public Domain
    ('Nocturne Op. 9 No. 2', 'Classical', 200, 0, 1),  -- Public Domain
    ('Blue Danube Waltz', 'Classical', 300, 0, 1),     -- Public Domain
    ('Prelude in E Minor', 'Classical', 150, 1, 2),    -- Creative Commons
    ('String Quartet No. 8', 'Classical', 100, 0, 3),  -- Copyright
    ('Guitar Serenade', 'Contemporary', 50, 1, 2),     -- Creative Commons
    ('Jazz Improv', 'Jazz', 75, 0, 3),                 -- Copyright
    ('Romantic Ballad', 'Romantic', 60, 1, 2);         -- Creative Commons

INSERT INTO Performance (musicId, userId, performanceDate, rating, reviewText) VALUES
    (1, 1, '2023-05-20', 5, 'A stunning rendition of Beethoven’s 5th Symphony!'),
    (2, 2, '2023-06-10', 4, 'Chopin’s Nocturne was beautifully performed.'),
    (3, 3, '2023-07-12', 3, 'The waltz performance lacked emotion.'),
    (4, 4, '2023-08-05', 4, 'Fantastic solo piano!'),
    (5, 1, '2023-09-01', 5, 'An intense quartet with a lot of depth.'),
    (6, 2, '2023-09-15', 3, 'Enjoyed the guitar serenade; good use of dynamics.'),
    (7, 3, '2023-09-20', 4, 'Great jazz improvisation!'),
    (8, 4, '2023-10-10', 2, 'Not my favorite piece, but well played.');

INSERT INTO MusicSheet_Instrument (musicId, instrId) VALUES
    (1, 3),  -- Symphony No. 5: Violin
    (1, 1),  -- Symphony No. 5: Piano
    (2, 1),  -- Nocturne Op. 9 No. 2: Piano
    (3, 3),  -- Blue Danube Waltz: Violin
    (4, 1),  -- Prelude in E Minor: Piano
    (5, 3),  -- String Quartet No. 8: Violin
    (6, 5),  -- Guitar Serenade: Guitar
    (7, 2),  -- Jazz Improv: Drums
    (8, 1),  -- Romantic Ballad: Piano
    (8, 5);  -- Romantic Ballad: Guitar

INSERT INTO MusicSheet_Album (musicId, albumId) VALUES
    (1, 1),  -- Symphony No. 5: Beethoven Complete Symphonies
    (2, 9),  -- Nocturne Op. 9 No. 2: Chopin Nocturnes
    (3, 5),  -- Blue Danube Waltz: Greatest Classical Hits
    (4, 10), -- Prelude in E Minor: Classical Moods for Study
    (5, 8),  -- String Quartet No. 8: Ultimate Guitar Anthems
    (6, 8),  -- Guitar Serenade: Ultimate Guitar Anthems
    (7, 7),  -- Jazz Improv: Jazz for the Soul
    (8, 6);  -- Romantic Ballad: Romantic Piano Classics

INSERT INTO Composer_MusicSheet (compId, musicId) VALUES
    (1, 1),  -- Ludwig van Beethoven: Symphony No. 5
    (2, 2),  -- Frederic Chopin: Nocturne Op. 9 No. 2
    (3, 3),  -- Johann Strauss: Blue Danube Waltz
    (2, 4),  -- Frederic Chopin: Prelude in E Minor
    (4, 5),  -- Franz Joseph Haydn: String Quartet No. 8
    (5, 7);  -- Dmitri Shostakovich: Jazz Improv


-- Update Beethoven's name for consistency in records, ensuring changes only affect composers born before 1800
UPDATE Composer
SET compName = 'L. Beethoven'
WHERE compName LIKE '%Beethoven%' AND birthDate <= '1800-01-01';

-- Increment the purchase count for popular music sheets with between 100 and 200 purchases
UPDATE MusicSheet
SET nrPurchases = nrPurchases + 5
WHERE nrPurchases BETWEEN 100 AND 200;

-- Update the description of the 'Copyright' License type
UPDATE License
SET description = 'It is restricted. It protects intellectual property'
WHERE licenseType = 'Copyright'

-- Delete the instruments that are in no category
DELETE FROM Instrument
WHERE category IS NULL;

-- Delete all composers with no music sheets on the platform
DELETE FROM Composer
WHERE compId NOT IN (
    SELECT DISTINCT compId 
    FROM Composer_MusicSheet
);


-- Queries
-- a. Union
-- Combine names of composers and platform users into a unique list of names with DISTINCT and ORDER BY
SELECT DISTINCT compName AS Name FROM Composer
UNION
SELECT DISTINCT username AS Name FROM PlatformUser
ORDER BY Name;

--
--List all composers which have Beethoven in their name and all users which have piano or music in their name
SELECT compName AS Name FROM Composer
WHERE compName LIKE '%Beethoven%'
UNION ALL
SELECT username AS Name FROM PlatformUser
WHERE username LIKE '%piano%' OR username IN (SELECT username as un FROM PlatformUser WHERE username LIKE '%music%');


-- b. Intersection
-- List user IDs that are both in the PlatformUser and Performance tables, with DISTINCT
SELECT DISTINCT userId FROM Performance
INTERSECT
SELECT DISTINCT userId FROM PlatformUser;

-- List music sheet IDs that are created and also performed, with an arithmetic expression to show total purchases with a purchase increase
SELECT DISTINCT musicId, (nrPurchases + 10) AS IncreasedPurchases
FROM MusicSheet
WHERE musicId IN (SELECT musicId FROM Performance)
ORDER BY IncreasedPurchases DESC;

-- c. Difference
-- List music sheet IDs that have not been performed and show their purchase counts increased by 10% using arithmetic in SELECT
SELECT musicId, (ROUND(nrPurchases * 1.1, 0)) AS AdjustedPurchases
FROM MusicSheet
WHERE musicId NOT IN (SELECT musicId FROM Performance);

-- Find platform user IDs with no performance records and use TOP to get only the first 5 users for review
SELECT TOP 5 userId FROM PlatformUser
EXCEPT
SELECT userId FROM Performance
ORDER BY userId;

-- d. Joins: inner, left, right, full. One query will join at least 3 tables. 
--			One will join at least two mtm relationships

-- List of users with their reviews and the titles of the music sheets they reviewed (INNER JOIN)
SELECT p.username, m.title, r.reviewText
FROM PlatformUser p
INNER JOIN Performance r ON p.userId = r.userId
INNER JOIN MusicSheet m ON r.musicId = m.musicId;

-- List of music sheets with album names, even if they aren't associated with an album (LEFT JOIN)
SELECT m.title, a.albumName
FROM MusicSheet m
LEFT JOIN MusicSheet_Album ma ON m.musicId = ma.musicId
LEFT JOIN Album a ON ma.albumId = a.albumId;


--
-- List of composers and the albums they appear in, including composers without albums and music sheets without composers (RIGHT JOIN)
SELECT DISTINCT c.compName, ms.musicId
FROM Composer c
RIGHT JOIN Composer_MusicSheet ms ON c.compId = ms.compId
RIGHT JOIN MusicSheet_Album ma on ms.musicId = ma.musicId
ORDER BY c.compName;

-- List of all users and their performance dates, even if some have not performed (FULL JOIN)
SELECT u.username, p.performanceDate
FROM PlatformUser u
FULL JOIN Performance p ON u.userId = p.userId;


-- e. 2 queries with the IN operator and a subquery in the WHERE clause; 
-- List titles of music sheets with 4-star or higher rating and increase purchase count by 5%
SELECT DISTINCT title, (nrPurchases + 5) AS IncreasedPurchases
FROM MusicSheet
WHERE musicId IN (SELECT musicId FROM Performance WHERE rating >= 4);

-- Find usernames of users who have performed at least one free music sheet or the music cheet has higher rating
SELECT DISTINCT username FROM PlatformUser
WHERE userId IN (
    SELECT userId FROM Performance 
    WHERE musicId IN (SELECT musicId FROM MusicSheet WHERE isFree = 1)
    OR NOT EXISTS (SELECT 1 FROM Performance WHERE rating < 3)
);


-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;
-- List titles of music sheets that have at least one performance rated above 3
SELECT title FROM MusicSheet m
WHERE EXISTS (SELECT 1 FROM Performance p WHERE p.musicId = m.musicId AND p.rating > 3);

-- List albums that contain at least one music sheet that is not free
SELECT albumName FROM Album a
WHERE EXISTS (SELECT 1 FROM MusicSheet_Album ma WHERE ma.albumId = a.albumId AND EXISTS (SELECT 1 FROM MusicSheet WHERE isFree = 0));


-- g. 2 queries with a subquery in the FROM clause;   
-- List each user with the total number of performances they have made
SELECT u.username, p.totalPerformances
FROM PlatformUser u
JOIN (SELECT userId, COUNT(*) AS totalPerformances FROM Performance GROUP BY userId) p ON u.userId = p.userId;

-- List top 10 albums and the total number of music sheets in each, ordered by number of music sheets
SELECT TOP 10 a.albumName, ms.totalSheets
FROM Album a
JOIN (
    SELECT albumId, COUNT(*) AS totalSheets 
    FROM MusicSheet_Album 
    GROUP BY albumId
) ms ON a.albumId = ms.albumId
ORDER BY ms.totalSheets;

-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
--			2 of the latter will also have a subquery in the HAVING clause; 
--			use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;
-- Count total music sheets by each composer
-- Count the total number of music sheets by each composer, with DISTINCT
SELECT DISTINCT compId, COUNT(musicId) AS totalSheets
FROM Composer_MusicSheet
GROUP BY compId;

-- Average rating by instrument with average rating above 3, ordered by instrument
SELECT DISTINCT instrId, AVG(rating) AS avgRating
FROM Performance p
JOIN MusicSheet_Instrument mi ON p.musicId = mi.musicId
GROUP BY instrId
HAVING AVG(rating) > 3
ORDER BY avgRating DESC;

-- Total purchases by genre, limited to genres with total purchases above the global average, with subquery in HAVING
SELECT DISTINCT genre, SUM(nrPurchases) AS totalPurchases
FROM MusicSheet
GROUP BY genre
HAVING SUM(nrPurchases) > (SELECT AVG(nrPurchases) FROM MusicSheet)
ORDER BY totalPurchases DESC;

-- Highest rating per user who meets or exceeds the highest recorded rating
SELECT DISTINCT userId, MAX(rating) AS maxRating
FROM Performance
GROUP BY userId
HAVING MAX(rating) >= ALL (SELECT rating FROM Performance WHERE rating IS NOT NULL);



-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); 
--			rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.
-- List usernames of users who have at least one performance with a rating above 4
SELECT DISTINCT username FROM PlatformUser
WHERE userId = ANY (SELECT userId FROM Performance WHERE rating > 4);

SELECT DISTINCT username 
FROM PlatformUser
WHERE userId IN (SELECT userId FROM Performance WHERE rating > 4);

--
--Select all composers whose compId is associated with all the music sheet in a particular album
SELECT compName
FROM Composer
WHERE compId = ALL (SELECT compId 
					FROM Composer_MusicSheet 
					WHERE musicId IN (SELECT musicId FROM MusicSheet_Album WHERE albumId = 1));
SELECT compName
FROM Composer
WHERE compId NOT IN (SELECT compId 
					FROM Composer_MusicSheet 
					WHERE musicId NOT IN (SELECT musicId FROM MusicSheet_Album WHERE albumId = 1));



-- Music sheets with a number of purchases greater than all purchases for free music sheet
SELECT musicId, title, nrPurchases
FROM MusicSheet
WHERE nrPurchases > ALL (SELECT nrPurchases 
                         FROM MusicSheet 
                         WHERE isFree = 1);

SELECT musicId, title, nrPurchases
FROM MusicSheet
WHERE nrPurchases > (SELECT MAX(nrPurchases) 
                     FROM MusicSheet 
                     WHERE isFree = 1);


-- Find composers which have a birthdate year greater than any composer who wrote a Classical music sheet
SELECT compId, compName, birthDate
FROM Composer
WHERE birthDate > ANY (SELECT birthDate 
					   FROM Composer c
					   JOIN Composer_MusicSheet cms on c.compId = cms.compId
                       JOIN MusicSheet ms ON cms.musicId = ms.musicId 
                       WHERE ms.genre = 'Classical');

SELECT compId, compName, birthDate
FROM Composer
WHERE birthDate > (SELECT MIN(birthDate)
                   FROM Composer c
                   JOIN Composer_MusicSheet cms ON c.compId = cms.compId 
                   JOIN MusicSheet ms ON cms.musicId = ms.musicId 
                   WHERE ms.genre = 'Classical');


-- You must use:

--arithmetic expressions in the SELECT clause in at least 3 queries;
--conditions with AND, OR, NOT, and parentheses in the WHERE clause in at least 3 queries;
--DISTINCT in at least 3 queries, ORDER BY in at least 2 queries, and TOP in at least 2 queries.