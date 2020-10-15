#include <minishell.h>

int		ft_echo(t_env *env, int fd_out, int fd_in, char **args)
{
	bool	nl_flag;

	fd_in = 0;
	if (!args || !(*args))
	{
		write(fd_out, "\n", 1);
		return (0);
	}
	nl_flag = (ft_strcmp(args[0], "-n") == 0)
		? false
		: true;
	args = (!nl_flag) ? args : args + 1;
	while (*args != NULL)
	{
		ft_putstr_fd(*args, fd_out);
		if (*(args + 1) != NULL)
			ft_putstr_fd(" ", fd_out);
		args++;
	}
	if (nl_flag)
		ft_putendl_fd(fd_out);
	return (0);
}
