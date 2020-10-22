#include <minishell.h>

bool			validate_executable_file(const char *filename)
{
	if (ft_strlen(filename) < 3)
		return (false);
	if (filename[0] == '.' && filename[1] == '/')
		return (true);
	if (filename[0] == '~' && filename[1] == '/')
		return (true);
	if (filename[0] == '.' && filename[1] == '.'
		&& filename[2] == '/')
		return (true);
	if (filename[0] == '/')
		return (true);
	return (false);
}

bool			validate_non_builtin_cmd(t_cmd *cmd, t_env *env)
{
	char		**paths;
	char		*valid_path;
	int			i;

	alloc_check(paths = ft_split(get_env_value(env, "PATH"), ':'));
	valid_path = ft_strdup(get_programm_path(cmd->name, paths));
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	if (valid_path == NULL)
	{
		if (validate_executable_file(cmd->name) == true)
			return (true);
		else
			return (false);
	}
	free(cmd->name);
	cmd->name = valid_path;
	return (true);
}
