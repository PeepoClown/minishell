#include <minishell.h>

void	add_to_env(t_env *env, const char *line)
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
