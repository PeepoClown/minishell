#include <minishell.h>

void	alloc_check(void *ptr)
{
	if (ptr != NULL)
		return ;
	ft_putstr_fd("bash : allocation error", 2);
	ft_putendl_fd(2);
	exit(ENOMEM);
}

void	ft_error(const char *cmd, const char *error, const char *desc)
{
	ft_putstr_fd("bash: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(desc, 2);
	ft_putendl_fd(2);
}
