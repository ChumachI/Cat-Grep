#!/bin/bash
SUCCESS=0
FAIL=0
DIFF_RES=""
FLAGS="-b -e -n -s -t -v"
#FLAGS="-b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank"
TEST_FILE="test.txt"
LOGER="cat_log.txt"
echo "" > cat_log.txt
echo " 	

 !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_\`abcdefghijklmnopqrstuvwxyz{\|}~" > test.txt

make -C . all -s

for var in $FLAGS
do
    TEST="$var $TEST_FILE"
    ./s21_cat $TEST > s21_cat.txt 
    cat $TEST > cat.txt
    if cmp -s s21_cat.txt cat.txt; then
        ((SUCCESS++))
    else
        echo $TEST >> $LOGER
        echo "$var"
        ((FAIL++))
    fi
     rm s21_cat.txt cat.txt
done


for var in $FLAGS 
do
 for var2 in $FLAGS
 do
    if [ $var != $var2 ]
    then
    TEST="$var $var2 $TEST_FILE"
    ./s21_cat $TEST > s21_cat.txt 
    cat $TEST > cat.txt
    if cmp -s s21_cat.txt cat.txt; then
        ((SUCCESS++))
    else
        echo $TEST >> $LOGER
        ((FAIL++))
    fi
     rm s21_cat.txt cat.txt
    fi
  done
done

for var in $FLAGS
do
 for var2 in $FLAGS
 do
  for var3 in $FLAGS
  do
    if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
    then
    TEST="$var $var2 $var3 $TEST_FILE"
    ./s21_cat $TEST > s21_cat.txt 
    cat $TEST > cat.txt
    if cmp -s s21_cat.txt cat.txt; then
        ((SUCCESS++))
    else
        echo $TEST >> $LOGER
        ((FAIL++))
    fi
     rm s21_cat.txt cat.txt
    fi
    done
  done
done


for var in $FLAGS
do
 for var2 in $FLAGS
 do
  for var3 in $FLAGS
  do
   for var4 in $FLAGS
   do
    if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
    then
    TEST="$var $var2 $var3 $var4 $TEST_FILE"
    ./s21_cat $TEST > s21_cat.txt 
    cat $TEST > cat.txt
    if cmp -s s21_cat.txt cat.txt; then
        ((SUCCESS++))
    else
        echo $TEST >> $LOGER
        ((FAIL++))
    fi
     rm s21_cat.txt cat.txt
    fi
     done
    done
  done
done

if [ $FAIL == 0 ]; then
    rm $LOGER
fi
rm $TEST_FILE
echo SUCCESS: $SUCCESS
echo FAIL: $FAIL