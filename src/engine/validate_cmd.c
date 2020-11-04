#include <minishell.h>

static	bool	validate_executable_file(const char *filename)
{
	if (ft_strlen(filename) < 3)
		return (false);
	if (filename[0] == '/')
		return (true);
	if (filename[0] == '.')
		return (true);
	if (filename[0] == '~')
		return (true);
	return (false);
}

bool			validate_non_builtin_cmd(t_cmd *cmd, t_env *env)
{
	char		**paths;
	char		*valid_path;

	if (validate_executable_file(cmd->name) == true)
		return (true);
	if (get_env_value(env, "PATH") != NULL)
		paths = ft_split(get_env_value(env, "PATH"), ':');
	else
		return (true);
	valid_path = get_programm_path(cmd->name, paths);
	ft_remove_char_matrix(paths);
	if (valid_path == NULL)
			return (false);
	free(cmd->name);
	cmd->name = valid_path;
	return (true);
}
