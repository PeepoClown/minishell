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

static	void	set_pwd(t_env *env, const char *type)
{
	char	*cwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	path = ft_strjoin(type, cwd);
	add_to_env(env, path);
	free(cwd);
	free(path);
}

int				ft_cd(t_cmd *cmd, t_env *env)
{
	char	*dest_path;
	char	*path_with_home;

	if (*(cmd->args) == NULL)
	{
		ft_error(cmd->name, NULL, "too few arguments");
		return (1);
	}
	path_with_home = replace_to_home(*(cmd->args));
	dest_path = (path_with_home != NULL)
				? path_with_home
				: *(cmd->args);
	set_pwd(env, "OLDPWD=");
	if ((chdir(dest_path) < 0))
	{
		if (path_with_home != NULL)
			free(path_with_home);
		ft_error(cmd->name, *(cmd->args), strerror(errno));
		return (1);
	}
	set_pwd(env, "PWD=");
	if (path_with_home != NULL)
		free(path_with_home);
	return (0);
}
