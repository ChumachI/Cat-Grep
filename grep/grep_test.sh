SUCCESS=0
FAIL=0
DIFF_RES=""
FLAGS="-i -v -c -l -n -h -s -o -iv -vi -ic -ci -il -li -in -ni -ih -hi -is -si -io -oi -vc -cv -vl -lv -vn -nv -vh -hv -vs -sv -cn -nc -ch -hc -co -oc -ln -nl -lh -hl -ls -sl -lo -ol -nh -hn -ns -sn -no -on -hs -sh -ho -oh -so -os -ei -ie -ev -ve -ec -ce -el -le -en -ne -eh -he -ef -es -se -eo -oe -if -vf -cf -lf -nf -hf -sf -of" 
TEST_FILE="test.txt"
LOGER="grep_log.txt"
TEMPLATE="elit"
TWO_TEMPLATES="-e elit -e Lorem"
TEMPLATE_FILE="-f templates.txt"
echo "" > grep_log.txt
echo "amet
elit
dui
mauris" > templates.txt
echo "Lorem ipsum dolor sit amet, consectetur adipiscing elit. 
Vivamus tristique dictum arcu, ac commodo nulla sodales sed. 
Sed vel turpis vitae metus tincidunt euismod. Nulla sed libero non ante dictum aliquam. 
Suspendisse potenti. Etiam interdum iaculis massa, nec suscipit mauris posuere sit amet. 
Sed at augue eu odio imperdiet 547 venenatis.

Nunc 129 ut hendrerit justo. Mauris sed velit ac augue convallis luctus. 
Nam euismod arcu et dui interdum malesuada. Maecenas in nunc ut mauris consequat malesuada. 
Fusce vel odio euismod, varius nulla vel, imperdiet ex. 
Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; 
Aenean euismod ex ac nulla tincidunt posuere." > test.txt

make -C . all -s

TEST="$TEMPLATE_FILE  $TEST_FILE"
./s21_grep  $TEST > s21_grep.txt 
grep $TEST > grep.txt
if cmp -s s21_grep.txt grep.txt; then
    ((SUCCESS++))
else
    echo $TEST >> $LOGER
    ((FAIL++))
fi
    rm s21_grep.txt grep.txt

TEST="$var $TWO_TEMPLATES $TEST_FILE"
./s21_grep  $TEST > s21_grep.txt 
grep  $TEST > grep.txt
if cmp -s s21_grep.txt grep.txt; then
    ((SUCCESS++))
else
    echo $TEST >> $LOGER
    ((FAIL++))
fi
    rm s21_grep.txt grep.txt

for var in $FLAGS
do
    TEST="$var $TEST_FILE"
    ./s21_grep $TEMPLATE  $TEST -s > s21_grep.txt 
    grep $TEMPLATE $TEST -s > grep.txt
    if cmp -s s21_grep.txt grep.txt; then
        ((SUCCESS++))
    else
        echo $TEST >> $LOGER
        ((FAIL++))
    fi
     rm s21_grep.txt grep.txt
done


if [ $FAIL == 0 ]; then
    rm $LOGER
fi
rm $TEST_FILE
rm $TEMPLATE_FILE
echo SUCCESS: $SUCCESS
echo FAIL: $FAIL