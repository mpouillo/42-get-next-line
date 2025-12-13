cc -Wall -Werror -Wextra -g -Dmalloc=test_malloc -DBUFFER_SIZE=1 get_next_line_bonus.c get_next_line_utils_bonus.c tests/main.c -o test.out \
&& gdb test.out \
&& rm test.out