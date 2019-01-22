#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	printf("%d\n", get_next_line(fd, &line));
	printf("fd from main - %d", fd);

	return (0);
}
