cc -Wall -Werror -Wextra -g -Dmalloc=test_malloc -DBUFFER_SIZE=1024 get_next_line_bonus.c get_next_line_utils_bonus.c tests/main.c -o test.out \
&& ./test.out "tests/testfd1.txt" "tests/testfd2.txt" "tests/testfd3.txt" \
&& rm test.out