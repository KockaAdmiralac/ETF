#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Missing argument"
    exit 1
fi
basedir="$1"
tmpfile="tmp.java"
dbfile="Banka_autoincrement.db"
workspace="$HOME/Temp/Eclipse"
projectroot="$workspace/BP1$basedir"

if [ `ls $projectroot/src | wc -l` -eq 0 ]
then
    for dir in $basedir/**
    do
        username=`echo $dir | sed s:$basedir/::`
        for file in $dir/*
        do
            cat "$file" | sed "s/package .*;/package $username;/" | tee "$tmpfile"
            cp "$tmpfile" "$file"
        done
    done
    cp -r $basedir/* "$projectroot/src"
    cp Postavka/$basedir/sqlite-jdbc-* "$projectroot"
else
    echo "Only copying DB"
fi

cp "Postavka/$basedir/$dbfile" "$projectroot"
rm "$tmpfile"
