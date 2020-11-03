#include <minishell.h>

int		ft_echo(t_cmd *cmd, t_env *env)
{
	bool	nl_flag;
	int		i;

	env = NULL;
	i = 0;
	if (*(cmd->args) == NULL)
	{
		ft_putendl_fd(cmd->fd_out);
		return (0);
	}
	nl_flag = (ft_strcmp(*(cmd->args), "-n") == 0) ? false : true;
	i = (nl_flag == false) ? 1 : 0;
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], cmd->fd_out);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", cmd->fd_out);
		i++;
	}
	if (nl_flag)
		ft_putendl_fd(cmd->fd_out);
	return (0);
}
