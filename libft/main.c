#include "includes/libft.h"
#include <fcntl.h>
#include "get_next_line/get_next_line.h"


int     main(int argc, char *argv[])
{
	int        fd;
	char    *line;
	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	fd = open("", O_RDONLY);
	while(get_next_line(fd, &line) == 1)
	{
		ft_putstr(line);
		ft_putchar('\n');
	}
	if (argc == 2)
		close(fd);
}
