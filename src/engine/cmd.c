#include <minishell.h>

static	void	set_command_fds(t_cmd *cmd, int *fd_out, int *fd_in)
{
	if (cmd->last_out_redir != NULL)
		*fd_out = open_output_redirect(cmd, *fd_out);
	if (cmd->redir_in != NULL)
		*fd_in = open_input_redirect(cmd, *fd_in);
	cmd->fd_out = *fd_out;
	cmd->fd_in = *fd_in;
}

static	int		execute(t_cmd *cmd, t_env *env)
{
	int		ret;

	if (cmd->builtin != NULL)
		ret = cmd->builtin->func(cmd, env);
	else
		ret = execute_programm(cmd, env);
	return (ret);
}

static	int		execute_command(t_cmd *cmd, t_env *env)
{
	int			ret;
	static	int	fd_out;
	static	int	fd_in;

	if (cmd->pipe_status == true)
		if (pipe(cmd->pipe) < 0)
		{
			ft_error("pipe", NULL, strerror(errno));
			return (errno);
		}
	fd_out = (cmd->pipe_status == true) ? cmd->pipe[WRITE_END] : STDOUT_FILENO;
	set_command_fds(cmd, &fd_out, &fd_in);
	ret = execute(cmd, env);
	if (cmd->pipe_status == true && cmd->last_out_redir == NULL)
		close(cmd->pipe[WRITE_END]);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	fd_in = (cmd->pipe_status == true) ? cmd->pipe[READ_END] : STDIN_FILENO;
	return (ret);
}

int				handle_cmd(t_cmd *cmd, t_env *env)
{
	int			status;

	errno = 0;
	// if (cmd->name == NULL)
	// 	return (status = g_status);
	validate_hidden_env(env, cmd); // ??? need tests
	if (cmd->name == NULL)
		return (status = 0);
	if (!validate_output_redirects(cmd) || !validate_input_redirects(cmd))
		return (status = 1);
	if ((cmd->builtin = get_builtin(cmd->name)) != NULL ||
			validate_non_builtin_cmd(cmd, env) == true)
		status = execute_command(cmd, env);
	else
	{
		ft_error(cmd->name, NULL, "command not found");
		status = 127;
	}
	return (status);
}
