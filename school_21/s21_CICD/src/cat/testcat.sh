#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

filenames=("test_1word.txt" "test_cols.txt" "test_empty.txt" "test_tab.txt" "test_text.txt")
for filename in "${filenames[@]}"; do
    #echo $filename
    #echo "---------------------*CAT -b"
    cat -b "$filename" > temp1.txt
    ./s21_cat -b "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        #diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT --number-nonblank"
    cat -b "$filename" > temp1.txt
    ./s21_cat --number-nonblank "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -e"
    cat -e "$filename" > temp1.txt
    ./s21_cat -e "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -E"
    cat -e "$filename" > temp1.txt
    ./s21_cat -E "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -n"
    cat -n "$filename" > temp1.txt
    ./s21_cat -n "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT --number"
    cat -n "$filename" > temp1.txt
    ./s21_cat --number "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -s"
    cat -s "$filename" > temp1.txt
    ./s21_cat -s "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT --squeeze-blank"
    cat -s "$filename" > temp1.txt
    ./s21_cat --squeeze-blank "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -t"
    cat -t "$filename" > temp1.txt
    ./s21_cat -t "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -b -n"
    cat -b -n "$filename" > temp1.txt
    ./s21_cat -b -n "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        #diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -b -s"
    cat -b -s "$filename" > temp1.txt
    ./s21_cat -b -s "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        #diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt

    #echo "---------------------*CAT -n -t -e"
    cat -n -t -e "$filename" > temp1.txt
    ./s21_cat -n -t -e "$filename" > temp2.txt
    if cmp -s temp1.txt temp2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        #diff temp1.txt temp2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm temp1.txt temp2.txt
done

# Выводим результаты
echo "Success count: $SUCCESS"
echo "Fail count: $FAIL"
echo "Total count: $COUNTER"

if [[ $FAIL -eq 0 ]]; then
    exit 0
else
    exit 1
fi