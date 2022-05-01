# get_next_line

A function that returns a line read from a file descriptor.

Repeated calls of get_next_line() function will let you read the text file pointed to by the file descriptor, one line at a time.

You can manage multiple file discriptor at the same time with *_bonus.c files.

## Usage

- normal
```
$ gcc -c get_next_line.c -D BUFFER_SIZE=<specify buffer size to read>
$ gcc -c get_next_line_util.c
$ gcc <your c file> get_next_line.o get_next_line_util.o
```

- bonus
```
$ gcc -c get_next_line_bonus.c -D BUFFER_SIZE=<specify buffer size to read>
$ gcc -c get_next_line_util_bonus.c
$ gcc <your c file> get_next_line_bonus.o get_next_line_util_bonus.o
```