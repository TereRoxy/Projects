-- ================================================
-- Template generated from Template Explorer using:
-- Create Procedure (New Menu).SQL
--
-- Use the Specify Values for Template Parameters 
-- command (Ctrl-Shift-M) to fill in the parameter 
-- values below.
--
-- This block of comments will not be included in
-- the definition of the procedure.
-- ================================================
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================

CREATE OR ALTER PROCEDURE PopulateLicense
	@numRows INT -- Number of rows to insert
AS
BEGIN
    DECLARE @counter INT = 1;

    PRINT 'Populating License table...';
    WHILE @counter <= @numRows
    BEGIN
        INSERT INTO License (licenseType, description)
        VALUES (
            CASE @counter % 3 
                WHEN 0 THEN 'Public Domain'
                WHEN 1 THEN 'Creative Commons'
                ELSE 'Copyright'
            END,
            'Description for license ' + CAST(@counter AS NVARCHAR)
        );
        SET @counter = @counter + 1;
    END;
    PRINT 'License table populated with ' + CAST(@numRows as nvarchar) + ' rows.';
END;
GO

CREATE OR ALTER PROCEDURE PopulateAlbum
	@numRows INT -- Number of rows to insert
AS
BEGIN
    DECLARE @counter INT = 1;

    PRINT 'Populating Album table...';
    WHILE @counter <= @numRows
    BEGIN
        INSERT INTO Album (albumName, albumYear)
        VALUES (
            'Album ' + CAST(@counter AS NVARCHAR),
            1980 + (@counter % 41) -- Random year between 1980 and 2021
        );
        SET @counter = @counter + 1;
    END;
    PRINT 'Album table populated with ' + CAST(@numRows as nvarchar) + ' rows.';
END;
GO


CREATE OR ALTER PROCEDURE PopulateMusicSheet
	@numRows INT -- Number of rows to insert
AS
BEGIN
    DECLARE @counter INT = 1;

    PRINT 'Populating MusicSheet table...';

	PRINT 'Num rows: ' + CAST (@numRows as nvarchar)
    WHILE @counter <= @numRows
    BEGIN
		DECLARE @licenseId INT = (@counter - 1 + (SELECT MIN(licenseId) FROM License));
		PRINT CAST (@licenseId as nvarchar) + CAST (@counter as nvarchar)
        INSERT INTO MusicSheet (title, genre, nrPurchases, isFree, license)
        VALUES (
            'Music Sheet ' + CAST(@counter AS NVARCHAR),
            CASE @counter % 4
                WHEN 0 THEN 'Classical'
                WHEN 1 THEN 'Pop'
                WHEN 2 THEN 'Rock'
                ELSE 'Jazz'
            END,
            FLOOR(RAND() * @numRows), -- Random number of purchases
            CASE WHEN @counter % 5 = 0 THEN 1 ELSE 0 END, -- 20% free sheets
            @licenseId
        );
        SET @counter = @counter + 1;

		PRINT 'COunter is: ' +  CAST (@counter as nvarchar)
    END;
    PRINT 'MusicSheet table populated with ' + CAST(@numRows as nvarchar ) + ' rows.';
END;
GO
