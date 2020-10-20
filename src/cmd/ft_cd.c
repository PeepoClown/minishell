#include <minishell.h>

int		ft_cd(t_cmd *cmd, t_env *env)
{
	char	path[PATH_MAX];
	char	*dest_path;
	char	*home_path;

	home_path = get_env_value(env, "HOME");
	dest_path = !(*(cmd->args)) ? home_path : *(cmd->args);
	if ((chdir(dest_path) < 0))
	{
		ft_error(cmd->name, *(cmd->args), strerror(errno));
		return (errno = 1);
	}
	return (0);
}
