#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#include "../get_next_line.h"

int	main(void)
{

	/* Test Mandatory */
	// write(1, "-- check mandatory --\n", 22);
	// char *r0;
	// int fd0 = open("test/case1.txt", O_RDONLY);
	// int i = 10;
	// while (i-- > 0)
	// {
	// 	r0 = get_next_line(fd0);
	// 	printf("%s", r0);
	// 	free(r0);
	// }

	/* Test stdin */
	// write(1, "-- check with stdin --\n", 23);
	// r0 = get_next_line(1);
	// printf("%s", r0);
	// free(r0);

	/* Test bonus */
	write(1, "-- check bonus --\n", 18);
	char *r1;
	char *r2;
	char *r3;
	int fd1 = open("test/case1.txt", O_RDONLY);
	int fd2 = open("test/case2.txt", O_RDONLY);
	int fd3 = open("test/case3.txt", O_RDONLY);
	int i = 10;
	while (i-- > 0)
	{
		r1 = get_next_line(fd1);
		printf("%s", r1);
		free(r1);
		r2 = get_next_line(fd2);
		printf("%s", r2);
		free(r2);
		r3 = get_next_line(fd3);
		printf("%s", r3);
		free(r3);
	}

	system("leaks a.out");
	
	return (0);
}
