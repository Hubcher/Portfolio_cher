#!/bin/bash

file="memcheck.txt"
var="-atExit -- ./s21_grep"

filenames=("test_1word.txt" "test_cols.txt" "test_empty.txt" "test_tab.txt" "test_text.txt" "test_rutext.txt")


for filename in "${filenames[@]}"; do
    echo "---------------------->>> FILENAME = $filename"

    echo "---------------------*grep -c student"
    leaks $var -c student "$filename" >> $file
    echo "---------------------*grep -l student"
    leaks $var -l student "$filename" >> $file
    echo "---------------------*grep -c -l student"
    leaks $var -c -l student "$filename" >> $file
    echo "---------------------*grep -cl student"
    leaks $var -cl student "$filename" >> $file
    echo "---------------------*grep -e was"
    leaks $var -e was -c "$filename" >> $file
    echo "---------------------*grep -f temp.txt"
    leaks $var -f temp.txt -c "$filename" >> $file
    echo "---------------------*grep-f temp.txt -e student"
    leaks $var -f temp.txt -e student "$filename" >> $file
    echo "---------------------*grep -e student -i"
    leaks $var -e student -i "$filename" >> $file
    echo "---------------------*grep -f temp.txt -i"
    leaks $var -f temp.txt -i "$filename" >> $file
    echo "---------------------*grep -e was -i -v"
    leaks $var -e was -i -v "$filename" >> $file
    echo "---------------------*grep -e was -e student -i"
    leaks $var -e was -e student -i "$filename" >> $file
    echo "---------------------*grep -f temp.txt -i -v"
    leaks $var -f temp.txt -i -v "$filename" >> $file
    echo "---------------------*grep -e was -ih"
    leaks $var -e was -ih "$filename" >> $file
    echo "---------------------*grep -e was -h"
    leaks $var -e was -h "$filename" test_text.txt >> $file
    echo "---------------------*grep -e was -s"
    leaks $var -e was -s "$filename" test_text.txt >> $file
    echo "---------------------*grep -f temp.txt -h"
    leaks $var -f temp.txt -h "$filename" test_text.txt >> $file
    echo "---------------------*grep -f temp.txt"
    leaks $var -f temp.txt "$filename" >> $file
    echo "---------------------*grep -f temp.txt -n"
    leaks $var -f temp.txt -n "$filename" >> $file
    echo "---------------------*grep -f t.txt -n"
    leaks $var -f t.txt -n "$filename" >> $file
    echo "---------------------*grep -e student -o"
    leaks $var -e student -o "$filename" >> $file
    echo "---------------------*grep -f temp.txt -o"
    leaks $var -f temp.txt -o "$filename" >> $file
    echo "---------------------*grep -f temp.txt -s"
    leaks $var -f temp.txt -s "$filename" >> $file
    
done
