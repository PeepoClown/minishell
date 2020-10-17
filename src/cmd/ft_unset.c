#include "minishell.h"

bool	arg_valid(const char *arg)
{
	int		delim_pos;

	if (!ft_isalpha(*arg) && !(*arg == '_'))
		return (false);
	arg++;
	while (*arg != '\0')
	{
		if (!ft_isalnum(*arg) && !(*arg == '_'))
			return (false);
		arg++;
	}
	return (true);
}

int		ft_unset(t_cmd *cmd, t_env *env)
{
	int		ret;

	if (!env)
		return (1);
	ret = 0;
	while (*(cmd->args) != NULL)
	{
		if (arg_valid(*(cmd->args)))
			del_env(&env, *(cmd->args));
		else
		{
			error_cmd("unset", *(cmd->args), "not a valid identifier");
			ret = 1;
		}
		(cmd->args)++;
	}
	return (ret);
}
