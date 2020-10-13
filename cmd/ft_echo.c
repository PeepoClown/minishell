#include "../minishell.h"

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);

int		ft_echo(t_cmd *cmd, int fd_out)
{
	bool	nl_flag;
	char	**args;

	if (!args || !(*args))
	{
		write(fd_out, "\n", 1);
		return (0);
	}
	nl_flag = (ft_strcmp(args[0], "-n") == 0)
		? false
		: true;
	args = (!nl_flag) ? cmd->args : cmd->args + 1;
	while (*args != NULL)
	{
		write(fd_out, *args, ft_strlen(*args));
		if (*(args + 1) != NULL)
			write(fd_out, " ", 1);
		args++;
	}
	if (nl_flag)
		write(fd_out, "\n", 1);
	return (0);
}
