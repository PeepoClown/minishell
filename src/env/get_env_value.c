#include <minishell.h>

bool	check_env_key(t_env *env, const char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
