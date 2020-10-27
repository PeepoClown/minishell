#include <minishell.h>

#define READ_END 0
#define WRITE_END 1

char	*g_user;
char	*g_home;
int	g_status;

static void	fork_child(t_cmd *commands, int *fd, t_env *env)
{
	close(fd[READ_END]);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		ft_error(NULL, NULL, "dup failed");
	close(fd[WRITE_END]);
	commands->fd_in = fd[READ_END];
	commands->fd_out = fd[WRITE_END];
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (!commands)
		exit(1);
	exit(0);
}

static void	fork_parent(t_cmd *commands, int *fd, t_env *env)
{
	close(fd[WRITE_END]);
	if (dup2(fd[READ_END], STDIN_FILENO) < 0)
		ft_error(NULL, NULL, "dup failed");
	close(fd[READ_END]);
	// if cmd have another pipe -> create_pipe call again
	commands->fd_in = fd[READ_END];
	commands->fd_out = fd[WRITE_END];
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (!commands)
		exit(1);
}

t_cmd		*create_pipe(t_cmd *commands, t_env *env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		ft_error(NULL, NULL, "pipe create error");
	pid = fork();
	if (pid < 0)
		ft_error(NULL, NULL, "fork failed");
	if (pid > 0)
		fork_parent(commands->next, fd, env);
	else
		fork_child(commands, fd, env);
	printf("zxc");
	return (commands);
}

int		main(int argc, char **argv, char **envp)
{
	t_env *env_list = create_env(envp);

	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->name = ft_strdup("echo");
	char *args[] = {"asd", NULL};
	cmd->args = args;

	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	cmd2->name = ft_strdup("cat");
	char *args2[] = {"-e", NULL};
	cmd2->args = args2;

	cmd->next = cmd2;
	cmd2->next = NULL;

	cmd = create_pipe(cmd, env_list);
	execute_cmd(cmd, env_list);
	execute_cmd(cmd2, env_list);
	return (0);
}