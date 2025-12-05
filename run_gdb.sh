cc -Wall -Werror -Wextra -g -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c tests/main.c -o test.out \
&& gdb test.out "tests/test_multiline_emptyline.txt" \
&& rm test.out