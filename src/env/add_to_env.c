#include <minishell.h>

void	add_to_env(t_env *env, const char *line)
{
	char	*key;

	key = (ft_find_first_of(line, '=') == -1)
		? ft_strdup(line)
		: ft_substr(line, 0, ft_find_first_of(line, '='));
	if (check_env_key(env, key) == true)
	{
		set_env_hidden(env, key, 0);
		if (ft_find_first_of(line, '=') >= 0)
			change_env_value(env, line);
		free(key);
		return ;
	}
	add_env(&env, line);
	if (ft_find_first_of(line, '=') == -1)
		set_env_hidden(env, key, 2);
	free(key);
}
