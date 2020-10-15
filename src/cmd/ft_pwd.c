#include <minishell.h>

int		ft_pwd(t_env *env, int fd_out, int fd_in, char **args)
{
	char	path[PATH_MAX];

	env = NULL;
	fd_in = 0;
	args = NULL;
	if (!getcwd(path, PATH_MAX))
	{
		error_cmd("pwd", NULL, strerror(errno));
		return (1);
	}
	ft_putstr_fd(path, fd_out);
	ft_putendl_fd(fd_out);
	return (0);
}
