#include "minishell.h"

// add error on allocation (if !memory -> error -> exit(1))

int		ft_error(int status, const char *error)
{
	ft_putstr_fd("shell: ", 2);
	if (error != NULL)
		ft_putstr_fd(error, 2);
	else
		strerror(status);
	ft_putendl_fd(2);
	if (status == ENOMEM)
		exit(status);
	return (status);
}

void	error_cmd(const char *cmd, const char *error, const char *desc)
{
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(desc, 2);
	ft_putendl_fd(2);
}
