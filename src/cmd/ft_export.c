#include <minishell.h>

static	bool	arg_valid(const char *arg)
{
	int		delim_pos;

	if (!ft_isalpha(*arg) && !(*arg == '_'))
		return (false);
	arg++;
	while (*arg != '\0')
	{
		if (*arg == '=')
			break ;
		if (!ft_isalnum(*arg) && !(*arg == '_'))
			return (false);
		arg++;
	}
	return (true);
}

static	void	empty_args_export(t_cmd *cmd, t_env *env)
{
	t_cmd	*copy;

	copy = copy_env(env);
	sort_env(&copy);
	print_env_export(copy, cmd->fd_out);
	remove_env(&copy);
}

int				ft_export(t_cmd *cmd, t_env *env)
{
	int		ret;

	if (!env)
		return (errno = 1);
	ret = 0;
	if (*(cmd->args) == NULL)
	{
		empty_args_export(cmd, env);
		return (ret);
	}
	while (*(cmd->args) != NULL)
	{
		if (arg_valid(*(cmd->args)))
			add_to_env(env, *(cmd->args));
		else
		{
			ft_error("export", *(cmd->args), "not a valid identifier");
			ret = 1;
		}
		(cmd->args)++;
	}
	return (ret);
}
