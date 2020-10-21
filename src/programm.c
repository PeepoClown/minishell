#include <minishell.h>

char			*get_programm_path(const char *cmd, char **paths)
{
	struct stat stat_buff;
	char		*res;
	int			i;
	char		*tmp1;
	char		*tmp2;

	i = 0;
	res = NULL;
	while (paths[i] != NULL)
	{
		tmp1 = ft_strjoin(paths[i], "/");
		tmp2 = tmp1;
		tmp1 = ft_strjoin(tmp1, cmd);
		free(tmp2);
		stat(tmp1, &stat_buff);
		if (S_ISREG(stat_buff.st_mode) == true)
		{
			res = tmp1;
			break ;
		}
		free(tmp1);
		i++;
	}
	return (res);
}

bool			validate_executable_file(const char *filename)
{
	if (ft_strlen(filename) < 3)
		return (false);
	if (filename[0] == '.' && filename[1] == '/')
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
	struct stat stat_buff;
	char		*valid_path;
	int			i;

	stat(cmd->name, &stat_buff);
	if (S_ISREG(stat_buff.st_mode) == true)
		if (validate_executable_file(cmd->name) == true)
			return (true);
	alloc_check(paths = ft_split(get_env_value(env, "PATH"), ':'));
	alloc_check(valid_path = ft_strdup(get_programm_path(cmd->name, paths)));
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	if (valid_path == NULL)
		return (false);
	free(cmd->name);
	cmd->name = valid_path;
	return (true);
}

char			**get_args_matrix(const char *cmd, char **args)
{
	char	**args_matrix;
	int		args_count;
	int		i;

	args_count = 0;
	while (args[args_count] != NULL)
		args_count++;
	if (!(args_matrix = (char**)malloc(sizeof(char*) * (args_count + 2))))
		return (NULL);
	i = 0;
	args_matrix[i] = ft_strdup(cmd);
	i++;
	while (i < (args_count + 1))
	{
		args_matrix[i] = ft_strdup(args[i - 1]);
		i++;
	}
	args_matrix[i] = NULL;
	return (args_matrix);
}

int				execute_programm(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	char	**env_matrix;
	char	**args_matrix;
	int		ret;

	pid = fork();
	if (pid < 0)
	{
		ft_error("fork", NULL, "failed");
		return (1);
	}
	else if (pid > 0)
		wait(&pid);
	else
	{
		alloc_check(env_matrix = get_env_matrix(env));
		alloc_check(args_matrix = get_args_matrix(cmd->name, cmd->args));
		ret = execve(cmd->name, args_matrix, env_matrix);
		ft_remove_char_matrix(args_matrix);
		ft_remove_char_matrix(env_matrix);
		if (ret < 0)
			ft_error(cmd->name, NULL, "no such command");
		exit(ret);
	}
	return (0);
}
