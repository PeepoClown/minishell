#include "minishell.h"

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
