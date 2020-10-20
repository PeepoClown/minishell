#include <minishell.h>

static	int		check_file_mode(const char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	printf("%s\n", filename);
	if (fd < 0)
		return (1);
	else
		return (0);
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
	return (false);
}

int				execute_file(t_cmd *cmd, t_env *env)
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
		if ((ret = check_file_mode(cmd->name)) != 0)
		{
			ft_error(cmd->name, NULL, strerror(errno));
			return (errno);
		}
		alloc_check(env_matrix = get_env_matrix(env));
		alloc_check(args_matrix = get_args_matrix(cmd->name, cmd->args));
		ret = execve(cmd->name, args_matrix, env_matrix);
		if (ret < 0)
			ft_error(NULL, NULL, "no such command");
		exit(ret);
	}
	return (0);
}