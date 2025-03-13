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

CREATE PROCEDURE VersionManager
    @targetVersion INT -- The target version to upgrade or downgrade to
AS
BEGIN
    -- Declare variables
    DECLARE @currentVersion INT;
    DECLARE @procedureName NVARCHAR(128);
    DECLARE @description NVARCHAR(255);
    DECLARE @sql NVARCHAR(MAX);

    -- Get the current version
    SELECT @currentVersion = versionNo FROM CurrentVersion;

    -- Validate the target version
    IF NOT EXISTS (SELECT 1 FROM CurrentVersion WHERE versionNo = @targetVersion)
    BEGIN
        PRINT 'Error: Target version does not exist in CurrentVersion.';
        RETURN;
    END;

    -- If the current version equals the target version, no operation is needed
    IF @currentVersion = @targetVersion
    BEGIN
        PRINT 'Database is already at the target version.';
        RETURN;
    END;

    -- Upgrade Path
    IF @currentVersion < @targetVersion
    BEGIN
        PRINT 'Upgrading database...';
        WHILE @currentVersion < @targetVersion
        BEGIN
            -- Move to the next version
            SET @currentVersion = @currentVersion + 1;

            -- Get the doProcedure for the next version
            SELECT @procedureName = doProcedure, @description = description
            FROM CurrentVersion WHERE versionNo = @currentVersion;

            -- Generate dynamic SQL to execute the procedure
            SET @sql = 'EXEC ' + @procedureName;
            EXEC sp_executesql @sql;

            -- Print status
            PRINT 'Upgraded to version ' + CAST(@currentVersion AS NVARCHAR) + ': ' + @description;
        END;
    END

    -- Downgrade Path
    ELSE IF @currentVersion > @targetVersion
    BEGIN
        PRINT 'Downgrading database...';
        WHILE @currentVersion > @targetVersion
        BEGIN
            -- Get the undoProcedure for the current version
            SELECT @procedureName = undoProcedure, @description = description
            FROM CurrentVersion WHERE versionNo = @currentVersion;

            -- Generate dynamic SQL to execute the procedure
            SET @sql = 'EXEC ' + @procedureName;
            EXEC sp_executesql @sql;

            -- Print status
            PRINT 'Downgraded from version ' + CAST(@currentVersion AS NVARCHAR) + ': ' + @description;

            -- Move to the previous version
            SET @currentVersion = @currentVersion - 1;
        END;
    END;

    -- Print completion status
    PRINT 'Database successfully updated to version ' + CAST(@targetVersion AS NVARCHAR) + '.';
END;

GO
