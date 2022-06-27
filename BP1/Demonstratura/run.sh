#!/bin/bash
mkdir -p out
rm -f out/prog
user="$1"
source=`find L1S/$user* -name "*.cpp"`
g++ -Wall -Wextra -g -lsqlite3 "$source" -o out/prog
if [ $? -eq 0 ]
then
    [ "$2" != "no" ] && cp Postavka/L1S/Banka_autoincrement.db out
    cd out
    ./prog
    echo -e "\n"
    sqlite3 -readonly Banka_autoincrement.db "SELECT * FROM Racun WHERE IdFil=2 OR IdFil=3" "SELECT * FROM Stavka WHERE IdSta >= 11" "SELECT * FROM Isplata WHERE IdSta >= 11"
fi
