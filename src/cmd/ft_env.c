#include "minishell.h"

int		ft_env(t_cmd *cmd, t_env *env)
{
	if (!env)
		return (1);
	print_env(env, cmd->fd_out);
	return (0);
}
