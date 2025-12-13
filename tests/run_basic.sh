cc -Wall -Werror -Wextra -g -Dmalloc=test_malloc -DBUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c tests/main.c -o test.out \
&& ./test.out "tests/test_single_char.txt" \
&& ./test.out "tests/test_single_char_newline.txt" \
&& ./test.out "tests/test_normal_line_newline.txt" \
&& ./test.out "tests/test_multiline_newline.txt" \
&& ./test.out "tests/test_multiline_emptyline.txt" \
&& ./test.out "tests/test_long_line.txt" \
&& ./test.out "tests/test_empty.txt" \
&& rm test.out