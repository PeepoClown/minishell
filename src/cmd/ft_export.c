#include <minishell.h>

bool	arg_valid(const char *arg)
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

t_env	*create_env_item_export(const char *key, const char *value)
{
	t_env	*item;

	if (!(item = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	item->key = ft_strdup(key);
	item->value = (value == NULL) ? NULL : ft_strdup(value);
	item->next = NULL;
	return (item);
}

void	add_arg_to_env(char *arg, t_env *env)
{
	int		delim_pos;
	char	*key;

	while (env->next != NULL)
		env = env->next;
	delim_pos = ft_find_first_of(arg, '=');
	if (delim_pos == -1)
		env->next = create_env_item_export(arg, NULL);
	else
	{
		key = ft_substr(arg, 0, delim_pos);
		env->next = create_env_item_export(key, arg + delim_pos + 1);
		free(key);
	}
}

int		ft_export(t_env *env, int fd_out, int fd_in, char **args)
{
	int		ret;

	ret = 0;
	fd_in = 0;
	if ((args == NULL) || (*args == NULL))
	{
		sort_env(&env);
		print_env_export(env, fd_out);
		return (ret);
	}
	while (*args != NULL)
	{
		if (arg_valid(*args))
			add_arg_to_env(*args, env);
		else
		{
			error_cmd("export", *args, "not a valid identifier");
			ret = 1;
		}
		args++;
	}
	return (ret);
}
