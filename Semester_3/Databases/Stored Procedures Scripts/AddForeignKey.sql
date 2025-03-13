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

CREATE PROCEDURE AddForeignKeyToPerformance
AS
BEGIN
    PRINT 'Adding foreign key to userId in Performance...';
    ALTER TABLE Performance
    ADD CONSTRAINT fk_performance_user FOREIGN KEY (userId) REFERENCES PlatformUser(userId); -- Add foreign key
    PRINT 'Foreign key added successfully.';
END;

GO
