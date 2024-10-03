/*								 */
/* TODO : put here a cool header */
/*								 */

#include <unistd.h>
#include <fcntl.h>

void fd_putstr(int fd, char *str)
{
	if (str == NULL)
	{
		fd_putstr(2, "ERROR: str to print is NULL.\n");
		return ;
	}
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		fd_putstr(2, "ERROR: input not correct.\n");
		return (0);
	}
	int fd = open(argv[1], O_RDONLY, NULL);
	if (fd < 0)
	{
		fd_putstr(2, "ERROR: input file could not be oppened.\n");
		return (0);
	}
	fd_putstr(1, "Test\n");
}
