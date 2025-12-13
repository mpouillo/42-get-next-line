cc -Wall -Werror -Wextra -O0 -Dmalloc=test_malloc -DBUFFER_SIZE=10 get_next_line_bonus.c get_next_line_utils_bonus.c tests/main.c -o test.out \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_empty.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_long_line.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_multiline_emptyline.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_multiline_newline.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_multiple_newline.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_normal_line_newline.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_single_char_newline.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_single_char.txt" \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out "tests/test_single_newline.txt" \
&& rm test.out