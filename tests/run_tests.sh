#!/bin/bash

./tests/compile_tests.sh  \
&& valgrind --leak-check=full --show-leak-kinds=all ./test.out $1 \
"tests/files/test_single_char.txt" \
"tests/files/test_single_char_newline.txt" \
"tests/files/test_normal_line_newline.txt" \
"tests/files/test_multiline_newline.txt" \
"tests/files/test_multiline_emptyline.txt" \
"tests/files/test_long_line.txt" \
"tests/files/test_empty.txt"