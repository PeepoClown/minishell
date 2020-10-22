#include <minishell.h>

static	char	*replace_to_home(char *path)
{
	char	*res;
	char	*tmp;

	if (path[0] != '~' || path[1] != '/')
		return (NULL);
	tmp = ft_substr(path, 1, ft_strlen(path));
	res = ft_strjoin(g_home, tmp);
	free(tmp);
	return (res);
}

int				ft_cd(t_cmd *cmd, t_env *env)
{
	char	path[PATH_MAX];
	char	*dest_path;
	char	*path_with_home;

	if (!(*(cmd->args)))
	{
		ft_error("cd", NULL, "too few arguments");
		return (errno = 1);
	}
	path_with_home = replace_to_home(*(cmd->args));
	dest_path = (path_with_home != NULL)
				? path_with_home
				: *(cmd->args);
	if ((chdir(dest_path) < 0))
	{
		if (path_with_home != NULL)
			free(path_with_home);
		ft_error(cmd->name, *(cmd->args), strerror(errno));
		return (errno = 1);
	}
	if (path_with_home != NULL)
		free(path_with_home);
	return (0);
}
