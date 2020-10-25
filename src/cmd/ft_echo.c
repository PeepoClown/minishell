#include <minishell.h>

int		ft_echo(t_cmd *cmd, t_env *env)
{
	bool	nl_flag;

	env = NULL;
	if (*(cmd->args) == NULL)
	{
		ft_putendl_fd(cmd->fd_out);
		return (0);
	}
	nl_flag = (ft_strcmp(*(cmd->args), "-n") == 0) ? false : true;
	cmd->args = (!nl_flag) ? cmd->args + 1 : cmd->args;
	while (*(cmd->args) != NULL)
	{
		ft_putstr_fd(*(cmd->args), cmd->fd_out);
		if (*(cmd->args + 1) != NULL)
			ft_putstr_fd(" ", cmd->fd_out);
		cmd->args++;
	}
	if (nl_flag)
		ft_putendl_fd(cmd->fd_out);
	return (0);
}
