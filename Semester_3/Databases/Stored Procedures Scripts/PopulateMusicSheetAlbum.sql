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
CREATE OR ALTER PROCEDURE PopulateMusicSheet_Album

	@numRows INT -- Number of rows to insert
AS
BEGIN
    -- Declare variables
    DECLARE @musicId INT, @albumId INT;
	DECLARE @counter int = 1;

    BEGIN TRY
        -- Populate MusicSheet_Album table
        PRINT 'Populating MusicSheet_Album table...';

        -- Loop through MusicSheet table
        DECLARE album_cursor CURSOR FOR
        SELECT albumId FROM Album;

        OPEN album_cursor;
        FETCH NEXT FROM album_cursor INTO @albumId;

        WHILE @counter<=@numRows
        BEGIN
            -- Assign 1-3 random music sheets to each album
            DECLARE @numMusic INT = FLOOR(RAND() * 3) + 1; -- 1 to 3 sheets per album
            DECLARE @i INT = 0;

            WHILE @i < @numMusic
            BEGIN
                -- Select a random music sheet
                SET @musicId = (SELECT TOP 1 musicId FROM MusicSheet ORDER BY NEWID());

                -- Insert the relationship into MusicSheet_Album
                IF NOT EXISTS (SELECT 1 FROM MusicSheet_Album WHERE musicId = @musicId AND albumId = @albumId)
                BEGIN
                    INSERT INTO MusicSheet_Album (musicId, albumId)
                    VALUES (@musicId, @albumId);
                END;

                SET @i = @i + 1;
            END;
			SET @counter = @counter + 1;
            FETCH NEXT FROM album_cursor INTO @albumId;
        END;

        CLOSE album_cursor;
        DEALLOCATE album_cursor;

        PRINT 'MusicSheet_Album table populated successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error: ' + ERROR_MESSAGE();
    END CATCH
END;
GO