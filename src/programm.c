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

static	int		programm_error(const char *cmd)
{
	if (errno == 0)
		return (0);
	ft_error(cmd, NULL, strerror(errno));
	if (errno == ENOENT)
		return (127);
	else
		return (126);
}

static	char	*replace_to_home(char *cmd)
{
	char	*res;
	char	*cuted_path;

	if (cmd[0] != '~' || cmd[1] != '/')
	{
		res = ft_strdup(cmd);
		free(cmd);
		return (res);
	}
	cuted_path = ft_substr(cmd, 1, ft_strlen(cmd));
	res = ft_strjoin(g_home, cuted_path);
	free(cuted_path);
	free(cmd);
	return (res);
}

int				execute_programm(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	char	**env_matrix;
	char	**args_matrix;
	int		ret;

	ret = 0;
	if ((pid = fork()) < 0)
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
		alloc_check(cmd->name = replace_to_home(cmd->name));
		ret = execve(cmd->name, args_matrix, env_matrix);
		ft_remove_char_matrix(args_matrix);
		ft_remove_char_matrix(env_matrix);
		exit(programm_error(cmd->name));
	}
	return (WEXITSTATUS(pid));
}
