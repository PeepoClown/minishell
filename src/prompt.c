#include "minishell.h"

static	char	*cut_home_path(t_env *env)
{
	char	*path;
	char	*home_path;
	char	*path_with_home;
	int		i;
	int		j;

	if (!(path = (char*)malloc(sizeof(char) * 4096)))
		return (NULL);
	getcwd(path, PATH_MAX);
	home_path = get_env_value(env, "HOME");
	path_with_home = ft_substr(path, 0, ft_strlen(home_path));
	if (ft_strcmp(path_with_home, home_path) == 0)
	{
		path_with_home = (char*)malloc(sizeof(char) * (ft_strlen(path) -
			ft_strlen(home_path) + 2));
		path_with_home[0] = '~';
		i = ft_strlen(home_path);
		j = 1;
		while (i < ft_strlen(path))
			path_with_home[j++] = path[i++];
		return (path_with_home);
	}
	else
		return (path);
}

void			display_prompt(t_env *env)
{
	char	*user;
	char	*path;

	user = get_env_value(env, "USER");
	path = cut_home_path(env);
	ft_putstr_fd("\e[1;35m", 1);
	ft_putstr_fd(user, 1);
	ft_putstr_fd("\e[0m:", 1);
	ft_putstr_fd("\e[1;33m", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\e[0m\n", 1);
	ft_putstr_fd("$> ", 1);
	free(path);
}
