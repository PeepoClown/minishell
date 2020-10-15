#include <minishell.h>

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
