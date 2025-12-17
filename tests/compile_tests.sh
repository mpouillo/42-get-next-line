#!/bin/bash

if [ -z "$1" ]; then
    SIZE="1024"
else
    SIZE="$1"
fi

cc -Wall -Werror -Wextra -g -Dmalloc=test_malloc -DBUFFER_SIZE=$SIZE get_next_line_bonus.c get_next_line_utils_bonus.c tests/main.c -o test.out