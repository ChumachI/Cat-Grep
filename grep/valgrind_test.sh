FLAGS="i v c l n h s o"

valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep elit test2.txt 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'

for var in $FLAGS
do
    valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -$var -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'  
    valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -$var -f templates2.txt test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
    valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -$var int test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
done
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -lv -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -liv -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -li -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -c -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -cv -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -ch -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -chi -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -ci -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -o -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -ov -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -oi -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -oiv -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -oin -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -onh -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -oinh -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -oinhs -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -in -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -nh -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -ns -e elit -e amet -e 123 test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./s21_grep -ns -f templates2.txt test2.txt test3.txt grep.c 2>&1| grep 'ERROR SUMMARY'