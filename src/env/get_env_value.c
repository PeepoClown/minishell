#include <minishell.h>

char	*get_env_value(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
