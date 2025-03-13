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

CREATE PROCEDURE RemoveUniqueKeyFromTitle
AS
BEGIN
    PRINT 'Removing unique key from title column in MusicSheet...';
    ALTER TABLE MusicSheet
    DROP CONSTRAINT uk_title; -- Remove unique constraint
    PRINT 'Unique key removed successfully.';
END;
GO
