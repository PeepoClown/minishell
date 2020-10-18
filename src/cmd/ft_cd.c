#include <minishell.h>

int		ft_cd(t_cmd *cmd, t_env *env)
{
	char	path[PATH_MAX];
	char	*dest_path;
	char	*home_path;
	int		args_count;

	args_count = 0;
	while (*(cmd->args + args_count) != NULL)
		args_count++;
	if (args_count > 1)
	{
		error_cmd(cmd->name, NULL, "too many arguments");
		return (1);
	}
	home_path = get_env_value(env, "HOME");
	dest_path = (args_count == 0) ? home_path : *(cmd->args);
	if ((chdir(dest_path) < 0))
	{
		error_cmd(cmd->name, *(cmd->args), strerror(errno));
		return (1);
	}
	return (0);
}
