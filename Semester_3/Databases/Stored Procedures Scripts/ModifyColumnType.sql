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
CREATE PROCEDURE ModifyEmailColumnType
AS
BEGIN
    PRINT 'Modifying the type of email column in PlatformUser...';
    ALTER TABLE PlatformUser
    ALTER COLUMN email NVARCHAR(100); -- Change email column to NVARCHAR(100)
    PRINT 'Column type modified successfully.';
END;


