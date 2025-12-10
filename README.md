# Get Next Line

*This project has been created as a part of the 42 curriculum by mpouillo.*

### Description:

Get Next Line is a project that requires writing a function in C that, upon each call, returns a single line read from the file descriptor passed as argument.

The function uses read() to get data from the file descriptor, restricted to the size specified as `BUFFER_SIZE` (1024 by default). The function loops this read() call to store data until it reaches either `\n` or EOF. When it does, the function returns the line read, or "NULL" if nothing was read or an error occured. Before returning, it stores the remaining data from the last read() call in a static variable, to save it for the next function call.

In the *bonus* version of the project, the function is able to manage multiple file descriptors at the same time, while still using a single static variable.

### Instructions

The prototype of `get_next_line()` is:
```c
char *get_next_line(int fd)
```

Compile with the following command, replacing `your_main.c` with a main function that calls `get_next_line()`:
```shell
cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c your_main.c
```

To compile with bonuses:
```shell
cc -Wall -Werror -Wextra get_next_line_bonus.c get_next_line_utils_bonus.c your_main.c
```

To change the allowed buffer size for read() calls, add the following compilation flag with a valid size: `-DBUFFER_SIZE=`

### Resources:

- [Project link](https://projects.intra.42.fr/projects/42cursus-get_next_line) (requires access to the 42 intra)
- AI was not used to create this project.
