#include <minishell.h>

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

// static	void	wait_child_pid(pid_t pid)
// {
// 	pid_t	res;
// 	int		status;

// 	while (true)
// 	{
// 		errno = 0;
// 		res = waitpid(pid, &status, WUNTRACED);
// 		if (errno != 0)
// 			ft_error(NULL, NULL, strerror(errno));
// 		if (g_sigint)
// 		{
// 			printf("%d - tobi pi... by %d\n", pid, SIGKILL);
// 			kill(pid, SIGKILL);
// 		}
// 		if (res >= 0)
// 			return ;
// 	}
// }

int				execute_programm(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	char	**env_matrix;
	char	**args_matrix;

	if ((pid = fork()) < 0)
	{
		ft_error("fork", NULL, strerror(errno));
		return (errno);
	}
	else if (pid > 0)
		wait(&pid);
		//wait_child_pid(&pid);
	else
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		dup2(cmd->fd_in, STDIN_FILENO);
		alloc_check(env_matrix = get_env_matrix(env));
		alloc_check(args_matrix = get_args_matrix(cmd->name, cmd->args));
		alloc_check(cmd->name = replace_to_home(cmd->name));
		execve(cmd->name, args_matrix, env_matrix);
		ft_remove_char_matrix(args_matrix);
		ft_remove_char_matrix(env_matrix);
		exit(programm_error(cmd->name));
	}
	if (WIFSIGNALED(pid))
		return (WTERMSIG(pid) + 128);
	return (WEXITSTATUS(pid));
}
