#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "../get_next_line.h"

int	main(void)
{
	char *r;

	int fd = open("test/case1.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("open error\n");
		return (1);
	}
	int i = 10;
	while (i-- > 0)
	{
		r = get_next_line(fd);
		printf("|%s|\n", r);
		free(r);
	}

	// write(1, "-- check with stdin --\n", 23);
	// r = get_next_line(1);
	// printf("|%s|\n", r);
	// free(r);
	
	system("leaks a.out");
	
	return (0);
}
