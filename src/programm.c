#include <minishell.h>

static	void	wait_child_pid()
{
	
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
		execve(cmd->name, args_matrix, env_matrix);
		ft_remove_char_matrix(args_matrix);
		ft_remove_char_matrix(env_matrix);
		exit(programm_error(cmd->name));
	}
	return (WEXITSTATUS(pid));
}
