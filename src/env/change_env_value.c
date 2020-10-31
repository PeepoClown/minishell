#include <minishell.h>

char	*change_env_value(t_env *env, const char *line)
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
	return (NULL);
}
