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
CREATE OR ALTER PROCEDURE AddTest
    @testName NVARCHAR(50),          -- Name of the test
    @tableIDs NVARCHAR(MAX),         -- Comma-separated list of Table IDs
    @positions NVARCHAR(MAX),        -- Comma-separated list of Positions for the tables
    @noOfRows NVARCHAR(MAX),         -- Comma-separated list of NoOfRows for each table
    @viewIDs NVARCHAR(MAX)           -- Comma-separated list of View IDs
AS
BEGIN
    DECLARE @testID INT;
    DECLARE @tableID INT, @position INT, @noOfRow INT, @viewID INT;

    BEGIN TRY
        -- Step 1: Add the test to the Tests table
        INSERT INTO Tests (Name)
        VALUES (@testName);
        SET @testID = SCOPE_IDENTITY(); -- Capture the TestID

        -- Step 2: Add tables for the test
        PRINT 'Adding tables for the test...';

        -- Parse and insert TableIDs, Positions, and NoOfRows
        DECLARE table_cursor CURSOR FOR SELECT value FROM STRING_SPLIT(@tableIDs, ',');
        OPEN table_cursor;
        FETCH NEXT FROM table_cursor INTO @tableID;

        DECLARE position_cursor CURSOR FOR SELECT value FROM STRING_SPLIT(@positions, ',');
        OPEN position_cursor;
        FETCH NEXT FROM position_cursor INTO @position;

        DECLARE rows_cursor CURSOR FOR SELECT value FROM STRING_SPLIT(@noOfRows, ',');
        OPEN rows_cursor;
        FETCH NEXT FROM rows_cursor INTO @noOfRow;

        WHILE @@FETCH_STATUS = 0
        BEGIN
            INSERT INTO TestTables (TestID, TableID, Position, NoOfRows)
            VALUES (@testID, @tableID, @position, @noOfRow);

            FETCH NEXT FROM table_cursor INTO @tableID;
            FETCH NEXT FROM position_cursor INTO @position;
            FETCH NEXT FROM rows_cursor INTO @noOfRow;
        END;

        CLOSE table_cursor;
        CLOSE position_cursor;
        CLOSE rows_cursor;

        DEALLOCATE table_cursor;
        DEALLOCATE position_cursor;
        DEALLOCATE rows_cursor;

        -- Step 3: Add views for the test
        PRINT 'Adding views for the test...';

        DECLARE view_cursor CURSOR FOR SELECT value FROM STRING_SPLIT(@viewIDs, ',');
        OPEN view_cursor;
        FETCH NEXT FROM view_cursor INTO @viewID;

        WHILE @@FETCH_STATUS = 0
        BEGIN
            INSERT INTO TestViews (TestID, ViewID)
            VALUES (@testID, @viewID);

            FETCH NEXT FROM view_cursor INTO @viewID;
        END;

        CLOSE view_cursor;
        DEALLOCATE view_cursor;

        PRINT 'Test successfully added with ID: ' + CAST(@testID AS NVARCHAR);
    END TRY
    BEGIN CATCH
        PRINT 'Error during Test Addition: ' + ERROR_MESSAGE();
    END CATCH
END;

GO
