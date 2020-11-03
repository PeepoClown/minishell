#include <minishell.h>

void	change_env_value(t_env *env, const char *line)
{
	char	*key;
	char	*value;

	key = ft_substr(line, 0, ft_find_first_of(line, '='));
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			break ;
		env = env->next;
	}
	free(key);
	if (env != NULL)
	{
		free(env->value);
		env->value = ft_substr(line, ft_find_first_of(line, '=') + 1,
			ft_strlen(line));
	}
}

void	set_env_hidden(t_env *env, const char *key, t_hidden_status status)
{
	if (!env)
		return ;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			break ;
		env = env->next;
	}
	if (env != NULL)
		env->is_hidden = status;
}
