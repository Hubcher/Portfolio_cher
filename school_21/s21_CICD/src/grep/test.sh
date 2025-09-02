#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0



filenames=("test_1word.txt" "test_cols.txt" "test_empty.txt" "test_tab.txt" "test_text.txt" "test_regex.txt" "test_rutext.txt")
for filename in "${filenames[@]}"; do
    #echo $filename
    
    grep -l student "$filename" > pattern1.txt
    ./s21_grep -l student "$filename" > pattern2.txt
    if cmp -s pattern1.txt pattern2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        #echo "---------------------*GREP -l"
        #echo "=== FAIL ==="
        # diff pattern1.txt pattern2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm pattern1.txt pattern2.txt

    # проваленный тест
    #grep -f temp.txt -i "$filename" > pattern1.txt
    #./s21_grep -f temp.txt -i "$filename" > pattern2.txt
    #if cmp -s pattern1.txt pattern2.txt; then
    #    SUCCESS=$((SUCCESS+1))
    #else
    #    FAIL=$((FAIL+1))
        # echo "---------------------*GREP -f -i"
        # echo "=== FAIL ==="
    #   diff pattern1.txt pattern2.txt
    #fi

    #COUNTER=$((COUNTER+1))
    #rm pattern1.txt pattern2.txt

    grep -e was -ih "$filename" > pattern1.txt
    ./s21_grep -e was -ih "$filename" > pattern2.txt
    if cmp -s pattern1.txt pattern2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        # echo "---------------------*GREP -e -ih"
        # echo "=== FAIL ==="
        # diff pattern1.txt pattern2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm pattern1.txt pattern2.txt

    grep -e was -h "$filename" test_text.txt > pattern1.txt
    ./s21_grep -e was -h "$filename" test_text.txt > pattern2.txt
    if cmp -s pattern1.txt pattern2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        # echo "---------------------*GREP -e -h"
        # echo "=== FAIL ==="
        # diff pattern1.txt pattern2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm pattern1.txt pattern2.txt

    
    grep -e was -s "$filename" test_text.txt > pattern1.txt
    ./s21_grep -e was -s "$filename" test_text.txt > pattern2.txt
    if cmp -s pattern1.txt pattern2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        # echo "---------------------*GREP -e -s"
        # echo "=== FAIL ==="
        # diff pattern1.txt pattern2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm pattern1.txt pattern2.txt

    grep -e student -o "$filename" > pattern1.txt
    ./s21_grep -e student -o "$filename" > pattern2.txt
    if cmp -s pattern1.txt pattern2.txt; then
        SUCCESS=$((SUCCESS+1))
    else
        FAIL=$((FAIL+1))
        # echo "---------------------*GREP -e -o"
        # echo "=== FAIL ==="
        # diff pattern1.txt pattern2.txt
    fi
    COUNTER=$((COUNTER+1))
    rm pattern1.txt pattern2.txt
done

echo "Success count: $SUCCESS"
echo "Fail count: $FAIL"
echo "Total count: $COUNTER"

if [[ $FAIL -eq 0 ]]; then
    exit 0
else
    exit 1
fi