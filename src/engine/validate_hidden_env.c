#include <minishell.h>

static	bool	validate_hidden_env_name(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name != '=')
	{
		if (!ft_isalpha(*name) && *name != '_' && !ft_isdigit(*name))
			return (false);
		name++;
	}
	return (true);
}

static	void	decrease_cmd_args(t_cmd *cmd)
{
	int		i;
	int		args_size;
	char	*tmp;

	args_size = 0;
	while (cmd->args[args_size] != NULL)
		args_size++;
	if (args_size == 1)
	{
		free(cmd->args[0]);
		cmd->args[0] = NULL;
		return ;
	}
	i = 0;
	while (i < args_size - 1)
	{
		tmp = cmd->args[i];
		cmd->args[i] = cmd->args[i + 1];
		free(tmp);
		i++;
	}
}

void			validate_hidden_env(t_env *env, t_cmd *cmd)
{
	char	*key;

	if (ft_find_first_of(cmd->name, '=') == -1)
		return ;
	if (validate_hidden_env_name(cmd->name) == false)
		return ;
	key = ft_substr(cmd->name, 0, ft_find_first_of(cmd->name, '='));
	if (check_env_key(env, key) == true)
		change_env_value(env, cmd->name);
	else
		add_to_env(env, cmd->name);
	set_env_hidden(env, key, 1);
	free(key);
	free(cmd->name);
	cmd->name = ft_strdup(cmd->args[0]);
	if (cmd->name == NULL)
		return ;
	decrease_cmd_args(cmd);
}
