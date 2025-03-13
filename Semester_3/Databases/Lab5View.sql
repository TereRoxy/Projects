USE [Music Sheet Platform];
GO

CREATE VIEW View_Ta_Tb_Tc
AS
SELECT 
    Tc.cid, 
    Ta.aid, Ta.a2, 
    Tb.bid, Tb.b2, 
    Tc.c2
FROM Tc
JOIN Ta ON Tc.aid = Ta.aid
JOIN Tb ON Tc.bid = Tb.bid;
