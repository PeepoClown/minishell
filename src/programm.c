#include <minishell.h>

char			*get_programm_path(const char *cmd, char **paths)
{
	struct stat stat_buff;
	char		*res;
	int			i;
	char		*tmp;

	i = 0;
	res = NULL;
	while (paths[i] != NULL)
	{
		paths[i] = ft_strjoin(paths[i], "/");
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(tmp);
		stat(paths[i], &stat_buff);
		if (S_ISREG(stat_buff.st_mode) == true)
		{
			res = paths[i];
			break ;
		}
		i++;
	}
	return (res);
}

static	void	set_programm_path(char **path, t_cmd *cmd, t_env *env)
{
	char	**paths;
	int		i;

	paths = ft_split(get_env_value(env, "PATH"), ':');
	*path = ft_strdup(get_programm_path(cmd->name, paths));
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
}

bool			validate_non_builtin_cmd(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	*valid_path;
	int		i;

	paths = ft_split(get_env_value(env, "PATH"), ':');
	valid_path = ft_strdup(get_programm_path(cmd->name, paths));
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	if (valid_path == NULL)
		return (false);
	free(valid_path);
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

// free !!!

int				execute_programm(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	char	**env_matrix;
	char	*path;
	char	**args_matrix;
	int		ret;

	pid = fork();
	if (pid < 0)
		ft_error("fork", NULL, "failed");
	else if (pid > 0)
		wait(&pid);
	else
	{
		alloc_check(env_matrix = get_env_matrix(env));
		set_programm_path(&path, cmd, env);
		alloc_check(path);
		alloc_check(args_matrix = get_args_matrix(cmd->name, cmd->args));
		ret = execve(path, args_matrix, env_matrix);
		if (ret < 0)
			ft_error(NULL, NULL, "no such command");
		exit(ret);
	}
	return (0);
}
