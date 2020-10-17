#include <minishell.h>

int		ft_cd(t_cmd *cmd, t_env *env)
{
	char	path[PATH_MAX];
	char	*dest_path;
	char	*home_path;

	home_path = get_env_value(env, "HOME");
	dest_path = (*(cmd->args) == NULL)
		? home_path
		: *(cmd->args);
	if ((chdir(dest_path) == -1))
	{
		error_cmd("cd", *(cmd->args), strerror(errno));
		return (1);
	}
	return (0);
}
