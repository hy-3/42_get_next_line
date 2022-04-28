#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "../get_next_line.h"

int	main(void)
{
	char *r;

	int fd1 = open("test/case1.txt", O_RDONLY);
	int fd2 = open("test/case2.txt", O_RDONLY);
	int fd3 = open("test/case3.txt", O_RDONLY);

	int i = 10;
	while (i-- > 0)
	{
		r = get_next_line(fd1);
		printf("|%s|\n", r);
		r = get_next_line(fd2);
		printf("|%s|\n", r);
		r = get_next_line(fd3);
		printf("|%s|\n", r);
	}

	// write(1, "-- check with stdin --\n", 23);
	// r = get_next_line(1);
	// printf("|%s|\n", r);
	// free(r);
	
	system("leaks a.out");
	
	return (0);
}
