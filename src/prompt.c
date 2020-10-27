#include <minishell.h>

void			init_prompt_vars(t_env *env)
{
	g_user = ft_strdup(get_env_value(env, "USER"));
	g_home = ft_strdup(get_env_value(env, "HOME"));
	g_status = 0;
}

void			remove_prompt_vars(char *user, char *home)
{
	free(user);
	free(home);
}

static	char	*cut_home_path(void)
{
	char	*path;
	char	*path_with_home;
	int		i;
	int		j;

	path = getcwd(NULL, PATH_MAX);
	path_with_home = ft_substr(path, 0, ft_strlen(g_home));
	if (ft_strcmp(path_with_home, g_home) == 0)
	{
		path_with_home = (char*)malloc(sizeof(char) * (ft_strlen(path) -
			ft_strlen(g_home) + 2));
		path_with_home[0] = '~';
		i = ft_strlen(g_home);
		j = 1;
		while (i < ft_strlen(path))
			path_with_home[j++] = path[i++];
		free(path);
		return (path_with_home);
	}
	else
	{
		free(path_with_home);
		return (path);
	}
}

void			display_prompt(void)
{
	char	*path;

	path = cut_home_path();
	ft_putstr_fd("\e[1;35m", 1);
	ft_putstr_fd(g_user, 1);
	ft_putstr_fd("\e[0m:", 1);
	ft_putstr_fd("\e[1;33m", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\e[0m\n", 1);
	ft_putstr_fd("$> ", 1);
	free(path);
}
