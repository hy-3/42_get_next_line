# get_next_line

It's a function that returns a line read from a file descriptor.

get_next_line() function will let you read one line at a time from the file descriptor you specified.

You can manage multiple file discriptors at the same time with *_bonus.c files.

## Overview
You can check the subject [here](https://github.com/hy-3/42_get_next_line/blob/master/getnextline.pdf)

## Usage
You can use get_next_line() function in your program.

```
-- overview --
$ gcc -c get_next_line.c -D BUFFER_SIZE=10 (<- arbitrary size)
(you can specify the buffer size for read. Either big or small, it will read one line at a time but the size affects to how many times read function will be called. Of course, more read will be called with smaller buffer size.)
$ gcc -c get_next_line_utils.c
$ gcc <your c file> get_next_line.o get_next_line_utils.o

-- ex) sample of reading each line from a file. --
$ vi input_1.txt
$ cat input_1.txt
aaaa
aaa
aa
a

$ vi main.c
$ cat main.c
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
int	main(void)
{
	char *str;
	int fd = open("input_1.txt", O_RDONLY);
	int i = 4;
	while (i-- > 0)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	}
	return (0);
}

$ gcc -c get_next_line.c -D BUFFER_SIZE=10
$ gcc -c get_next_line_utils.c
$ gcc main.c get_next_line.o get_next_line_utils.o
$ ./a.out
```

[bonus]
```
-- overview --
$ gcc -c get_next_line_bonus.c -D BUFFER_SIZE=10 (<- arbitrary size)
(you can specify the buffer size for read. Either big or small, it will read one line at a time but the size affects to how many times read function will be called. Of course, more read will be called with smaller buffer size.)
$ gcc -c get_next_line_utils_bonus.c
$ gcc <your c file> get_next_line_bonus.o get_next_line_utils_bonus.o

-- ex) sample of reading each line from multiple files. --
$ vi input_1.txt
$ cat input_1.txt
aaaa
aaa
aa
a

$ vi input_2.txt
$ cat input_2.txt
bbbb
bbb
bb
b

$ vi main.c
$ cat main.c
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"
int	main(void)
{
	char *str1;
	char *str2;
	int fd1 = open("input_1.txt", O_RDONLY);
	int fd2 = open("input_2.txt", O_RDONLY);
	int i = 4;
	while (i-- > 0)
	{
		str1 = get_next_line(fd1);
		printf("%s", str1);
		free(str1);
		str2 = get_next_line(fd2);
		printf("%s", str2);
		free(str2);
	}
	return (0);
}

$ gcc -c get_next_line_bonus.c -D BUFFER_SIZE=10
$ gcc -c get_next_line_utils_bonus.c
$ gcc main.c get_next_line_bonus.o get_next_line_utils_bonus.o
$ ./a.out
```
