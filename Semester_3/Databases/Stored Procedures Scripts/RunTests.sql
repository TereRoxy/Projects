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
CREATE OR ALTER PROCEDURE RunTest
    @testID INT,           -- Test ID from the Tests table
    @testName NVARCHAR(50) -- Name of the test
AS
BEGIN
    -- Declare variables
    DECLARE @testRunID INT;
    DECLARE @tableID INT, @viewID INT, @position INT, @noOfRows INT;
    DECLARE @startTime DATETIME, @endTime DATETIME;
    DECLARE @tableName NVARCHAR(128);
	DECLARE @viewName NVARCHAR(128);
    DECLARE @sql NVARCHAR(MAX);

    BEGIN TRY
        -- Step 1: Log the Test Run
        INSERT INTO TestRuns (Description, StartAt)
        VALUES ('Running Test: ' + @testName, GETDATE());
        SET @testRunID = SCOPE_IDENTITY(); -- Capture the TestRunID

        -- Step 2: Delete data from test tables in the specified order
        PRINT 'Deleting data for Test ID ' + CAST(@testID AS NVARCHAR);

        -- Select tables for deletion in correct order
        DECLARE delete_cursor CURSOR FOR
        SELECT T.TableID, T.Position, Tables.Name
        FROM TestTables T
        JOIN Tables ON T.TableID = Tables.TableID
        WHERE T.TestID = @testID
        ORDER BY T.Position ASC;

        OPEN delete_cursor;
        FETCH NEXT FROM delete_cursor INTO @tableID, @noOfRows, @tableName;

		-----------------------------------------------------------
        WHILE @@FETCH_STATUS = 0
        BEGIN
            SET @sql = 'DELETE FROM ' + @tableName;
            EXEC sp_executesql @sql; -- Execute the dynamic DELETE statement

            FETCH NEXT FROM delete_cursor INTO @tableID, @noOfRows, @tableName;
        END;
        CLOSE delete_cursor;
        DEALLOCATE delete_cursor;

        -- Step 3: Insert data into test tables in reverse order
        PRINT 'Inserting data for Test ID ' + CAST(@testID AS NVARCHAR);

        DECLARE insert_cursor CURSOR FOR
        SELECT T.TableID, T.NoOfRows, Tables.Name
        FROM TestTables T
        JOIN Tables ON T.TableID = Tables.TableID
        WHERE T.TestID = @testID
        ORDER BY T.Position DESC;

        OPEN insert_cursor;
        FETCH NEXT FROM insert_cursor INTO @tableID, @noOfRows, @tableName;

		--------------------------------------------------------------------- populate the required number of rows
        WHILE @@FETCH_STATUS = 0
        BEGIN
            SET @startTime = GETDATE();
            SET @sql = 'Populate' + @tableName + ' @numRows = ' + CAST(@noOfRows as nvarchar); -- Dynamic INSERT statement for testing
            EXEC sp_executesql @sql;
            SET @endTime = GETDATE();

            -- Log INSERT performance in TestRunTables
            INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
            VALUES (@testRunID, @tableID, @startTime, @endTime);

            FETCH NEXT FROM insert_cursor INTO @tableID, @noOfRows, @tableName;
        END;
        CLOSE insert_cursor;
        DEALLOCATE insert_cursor;

        -- Step 4: Evaluate views for the test
        PRINT 'Evaluating views for Test ID ' + CAST(@testID AS NVARCHAR);

        DECLARE view_cursor CURSOR FOR
        SELECT TV.ViewID, Views.Name
        FROM TestViews TV
        JOIN Views ON TV.ViewID = Views.ViewID
        WHERE TV.TestID = @testID;

        OPEN view_cursor;
        FETCH NEXT FROM view_cursor INTO @viewID, @viewName;

        WHILE @@FETCH_STATUS = 0
		---------------------------------------------------------------------------------- call the right views
        BEGIN
            SET @startTime = GETDATE();
            SET @sql = 'SELECT * FROM ' + QUOTENAME(@viewName);
            EXEC sp_executesql @sql;
            SET @endTime = GETDATE();

            -- Log SELECT performance in TestRunViews
            INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
            VALUES (@testRunID, @viewID, @startTime, @endTime);

            FETCH NEXT FROM view_cursor INTO @viewID, @viewName;
        END;
        CLOSE view_cursor;
        DEALLOCATE view_cursor;

        -- Step 5: Finalize the Test Run
        UPDATE TestRuns
        SET EndAt = GETDATE()
        WHERE TestRunID = @testRunID;

        PRINT 'Test run completed successfully for Test ID ' + CAST(@testID AS NVARCHAR);
    END TRY
    BEGIN CATCH
        PRINT 'Error during Test Execution: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;
GO
