#!/bin/bash

# RUN FROM GNL ROOT FOLDER WITH ./tests/run_tests [BUFFER_SIZE] [--bonus]

BUFFER_SIZE=
ARG=

if [[ "$1" = "--bonus" ]]; then
	BONUS_FLAG=1
	BUFFER_SIZE="$2"
elif [[ "$2" = "--bonus" ]]; then
	BONUS_FLAG=1
	BUFFER_SIZE="$1"
else
    BONUS_FLAG=0
	BUFFER_SIZE="$1"
fi

if [[ $BONUS_FLAG -eq 1 ]]; then
	ARG="--bonus"
fi

./tests/compile_tests.sh $BUFFER_SIZE && \
valgrind --leak-check=full --show-leak-kinds=all ./test.out $ARG \
"tests/files/test_single_char.txt" \
"tests/files/test_single_char_newline.txt" \
"tests/files/test_normal_line_newline.txt" \
"tests/files/test_multiline_newline.txt" \
"tests/files/test_multiline_emptyline.txt" \
"tests/files/test_long_line.txt" \
"tests/files/test_empty.txt"
