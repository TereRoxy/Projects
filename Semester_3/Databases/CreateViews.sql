-- Provides basic information about music sheets.
CREATE VIEW View_MusicSheetInfo AS
SELECT 
    musicId,
    title,
    genre
FROM 
    MusicSheet;

--Joins MusicSheet with License to include license details for each music sheet.
CREATE VIEW View_MusicSheetLicense AS
SELECT 
    ms.musicId,
    ms.title,
    ms.genre,
    ms.nrPurchases,
    ms.isFree,
    l.licenseType,
    l.description AS licenseDescription
FROM 
    MusicSheet ms
JOIN 
    License l ON ms.license = l.licenseId;


--Joins Album, MusicSheet_Album, and MusicSheet to summarize the total number of music sheets linked to each album
CREATE VIEW View_AlbumMusicSheetSummary AS
SELECT 
    a.albumName,
    COUNT(msa.musicId) AS TotalMusicSheets
FROM 
    Album a
JOIN 
    MusicSheet_Album msa ON a.albumId = msa.albumId
JOIN 
    MusicSheet ms ON msa.musicId = ms.musicId
GROUP BY 
    a.albumName;

