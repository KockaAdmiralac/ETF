#!/bin/bash
sqlite3 -readonly ~/Temp/Eclipse/BP1L1R/Banka_autoincrement.db "SELECT * FROM Racun WHERE IdRac=4" "SELECT * FROM Stavka WHERE IdSta=11" "SELECT * FROM Uplata WHERE IdSta=11"
