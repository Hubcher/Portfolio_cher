#!/bin/bash

file="memcheck.txt"
var="-atExit -- ./s21_cat"

filenames=("test_1word.txt" "test_cols.txt" "test_empty.txt" "test_tab.txt" "test_text.txt" "test_rutext.txt")

for filename in "${filenames[@]}"; do
    echo ">>> FILENAME = $filename"
    echo "---------------------CAT -b"
    leaks $var -b "$filename" >> $file

    echo "---------------------*CAT --number-nonblank"
    leaks $var --number-nonblank "$filename" >> $file

    echo "---------------------*CAT -e"
    leaks $var -e "$filename" >> $file

    echo "---------------------*CAT -E" 
    leaks $var -E "$filename" >> $file 

    echo "---------------------*CAT -n" 
    leaks $var -n "$filename" >> $file 

    echo "---------------------*CAT --number" 
    leaks $var --number "$filename" >> $file 

    echo "---------------------*CAT -s" 
    leaks $var -s "$filename" >> $file

    echo "---------------------*CAT --squeeze-blank" 
    leaks $var --squeeze-blank "$filename" >> $file 

    echo "---------------------*CAT -t" 
    leaks $var -t "$filename" >> $file 

    echo "---------------------*CAT -T" 
    leaks $var -T "$filename" >> $file 

    echo "---------------------*CAT -b -n" 
    leaks $var -b -n "$filename" >> $file 

    echo "---------------------*CAT -b -s" 
    leaks $var -b -s "$filename" >> $file 

    echo "---------------------*CAT -b -s -t -e" 
    leaks $var -b -s -t -e "$filename" >> $file 

    echo "---------------------*CAT --number-nonblank --squeeze-blank -t -e" 
    leaks $var --number-nonblank --squeeze-blank -t -e "$filename" >> $file 

    echo "---------------------*CAT -n -t -e" 
    leaks $var -n -t -e "$filename" >> $file 

done
