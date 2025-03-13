USE [Music Sheet Platform];
GO

CREATE TABLE Ta (
    aid INT PRIMARY KEY CLUSTERED,
    a2 INT UNIQUE, -- Nonclustered index will be automatically created
    a3 INT
);

CREATE TABLE Tb (
    bid INT PRIMARY KEY CLUSTERED,
    b2 INT,
    b3 INT
);

CREATE TABLE Tc (
    cid INT PRIMARY KEY CLUSTERED,
    aid INT FOREIGN KEY REFERENCES Ta(aid),
    bid INT FOREIGN KEY REFERENCES Tb(bid),
    c2 INT
);


-- a. Write queries on Ta such that their execution plans contain the following operators:

-- clustered index scan;
SELECT * FROM Ta
-- the query retrieves all rows without a filtering condition.


-- clustered index seek;
SELECT * 
FROM Ta
WHERE aid = 10;
-- clustered index seek because aid is the primary key with a clustered index, and the query filters on this column.


-- nonclustered index scan;
SELECT a2 
FROM Ta;
-- nonclustered index scan because the query retrieves all rows from a2, which has a nonclustered index automatically created

-- nonclustered index seek;
SELECT a2
FROM Ta
WHERE a2 = 20; -- seek, uses a2 to filter, which has a nonclustered index


-- key lookup
SELECT a2, a3 -- a3 isn't in a default clustered/nonclustered index, it is an additional column, so the query performs a nonclustered seek on a2 and a key lookup un a3
FROM Ta
WHERE a2 = 20;


-- b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. 
-- Create a nonclustered index that can speed up the query. Examine the execution plan again.
SELECT * 
FROM Tb
WHERE b2 = 50;

CREATE NONCLUSTERED INDEX IX_Tb_b2 
ON Tb (b2);

DROP INDEX Tb.IX_Tb_b2

-- c. Create a view that joins at least 2 tables. 
-- Check whether existing indexes are helpful; if not, reassess existing indexes / examine the cardinality of the tables.
SELECT * FROM View_Ta_Tb_Tc WHERE a2 = 20;

CREATE NONCLUSTERED INDEX IX_Tc_aid_bid_c2
ON Tc (aid, bid, c2);

DROP INDEX Tc.IX_Tc_aid_bid_c2

-- Populate Ta
EXEC sp_executesql N'
DECLARE @counter INT = 1;
DECLARE @totalRows INT = 1000;
WHILE @counter <= @totalRows
BEGIN
    INSERT INTO Ta (aid, a2, a3)
    VALUES (@counter, @counter * 10, RAND() * 1000);
    SET @counter = @counter + 1;
END;
';

-- Populate Tb
EXEC sp_executesql N'
DECLARE @counter INT = 1;
DECLARE @totalRows INT = 500;
WHILE @counter <= @totalRows
BEGIN
    INSERT INTO Tb (bid, b2, b3)
    VALUES (@counter, @counter % 50, RAND() * 500);
    SET @counter = @counter + 1;
END;
';

-- Populate Tc
EXEC sp_executesql N'
DECLARE @counter INT = 1;
DECLARE @totalRows INT = 800;
DECLARE @aid INT, @bid INT;
WHILE @counter <= @totalRows
BEGIN
    SET @aid = 1 + FLOOR(RAND() * 1000);
    SET @bid = 1 + FLOOR(RAND() * 500);
    INSERT INTO Tc (cid, aid, bid, c2)
    VALUES (@counter, @aid, @bid, RAND() * 100);
    SET @counter = @counter + 1;
END;
';

SELECT COUNT(*) AS TotalRows FROM Tc;
