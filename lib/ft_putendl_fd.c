#include <lib.h>

void	ft_putendl_fd(int fd)
{
	write(fd, "\n", 1);
}
