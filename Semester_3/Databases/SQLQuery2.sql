EXEC VersionManager @targetVersion = 1;

SELECT DB_NAME() AS CurrentDatabase;

SELECT name, default_database_name
FROM sys.server_principals
WHERE name = SUSER_NAME();

select * from CurrentVersion
select * from VersionMapping

insert into  CurrentVersion values (0);
UPDATE CurrentVersion set versionNo = 3
