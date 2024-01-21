FLAGS="i v c l n h s o"

leaks -quiet -atExit -- ./s21_grep elit test2.txt 
leaks -quiet -atExit -- ./s21_grep -e elit -e amet -e 123 test2.txt test3.txt grep.c 

for var in $FLAGS
do
    leaks -quiet -atExit -- ./s21_grep -$var -e elit -e amet -e 123 test2.txt test3.txt grep.c 
    leaks -quiet -atExit -- ./s21_grep -$var -f templates2.txt test2.txt test3.txt grep.c 
    leaks -quiet -atExit -- ./s21_grep -$var int test2.txt test3.txt grep.c 
done
leaks -quiet -atExit -- ./s21_grep -lv -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -liv -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -li -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -c -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -cv -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -ch -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -chi -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -ci -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -o -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -ov -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -oi -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -oiv -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -oin -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -onh -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -oinh -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -oinhs -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -in -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -nh -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -ns -e elit -e amet -e 123 test2.txt test3.txt grep.c 
leaks -quiet -atExit -- ./s21_grep -ns -f templates2.txt test2.txt test3.txt grep.c 