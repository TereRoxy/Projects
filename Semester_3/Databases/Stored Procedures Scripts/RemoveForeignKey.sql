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
CREATE PROCEDURE RemoveForeignKey
    @tableName NVARCHAR(128),
    @constraintName NVARCHAR(128)
AS
BEGIN
    PRINT 'Removing foreign key...';
    DECLARE @sql NVARCHAR(MAX);
    SET @sql = 'ALTER TABLE ' + @tableName + ' DROP CONSTRAINT ' + @constraintName;
    EXEC sp_executesql @sql;
    PRINT 'Foreign key removed successfully.';
END
GO
