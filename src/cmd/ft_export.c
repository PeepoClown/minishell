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

void			add_to_env(t_env *env, const char *line)
{
	char	*key;

	key = (ft_find_first_of(line, '=') == -1)
		? ft_strdup(line)
		: ft_substr(line, 0, ft_find_first_of(line, '='));
	if (check_env_key(env, key) == true)
	{
		if (ft_find_first_of(line, '=') == -1)
		{
			free(key);
			return ;
		}
		change_env_value(env, line);
		return ;
	}
	free(key);
	add_env(&env, line);
}

int				ft_export(t_cmd *cmd, t_env *env)
{
	int		ret;

	if (!env)
		return (errno = 1);
	ret = 0;
	if (*(cmd->args) == NULL)
	{
		sort_env(&env);
		print_env_export(env, cmd->fd_out);
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
