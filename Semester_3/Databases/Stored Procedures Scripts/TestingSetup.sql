INSERT INTO Views (Name)
VALUES
    ('View_MusicSheetInfo'),          
    ('View_MusicSheetLicense'),       
    ('View_AlbumMusicSheetSummary');

INSERT INTO Tables(Name)
VALUES
	('MusicSheet_Album'),
	('MusicSheet'),
	('Album'),
	('License');


EXEC AddTest 
    @testName = 'Test2',
    @tableIDs = '1,2,4',
    @positions = '1,2,3',
    @noOfRows = '100,200,500',
    @viewIDs = '1,2,3';

DECLARE @testRunID INT;
EXEC RunTest @testID = 2, @testName = 'Test2';

SELECT* from TestTables
SELECT * FROM License
SELECT * FROM MusicSheet

SELECT * FROM Tables

SELECT * FROM Tests
SELECT * FROM Views
SELECT * FROM TestViews
SELECT * FROM TestTables

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews