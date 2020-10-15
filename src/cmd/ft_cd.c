#include <minishell.h>

int		ft_cd(t_env *env, int fd_out, int fd_in, char **args)
{
	char	path[PATH_MAX];
	char	*dest_path;
	char	*home_path;

	fd_out = 1;
	fd_in = 0;
	home_path = get_env_value(env, "HOME");
	dest_path = (ft_strcmp(args[0], "") == 0)
		? home_path
		: args[0];
	if ((chdir(dest_path) == -1))
	{
		error_cmd("cd", args[0], strerror(errno));
		return (1);
	}
	return (0);
}
