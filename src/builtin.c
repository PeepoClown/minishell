#include <minishell.h>

void		remove_builtin(t_builtin *builtin)
{
	free(builtin->cmd);
	free(builtin);
}

t_builtin	*get_builtin(const char *cmd_name)
{
	const t_builtin	builtins[7] = { { "echo", ft_echo }, { "cd", ft_cd },
		{ "pwd", ft_pwd }, { "export", ft_export }, { "env", ft_env },
		{ "unset", ft_unset }, { "exit", ft_exit } };
	t_builtin		*res;
	int 			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd_name, builtins[i].cmd) == 0)
			break ;
		i++;
	}
	res = NULL;
	if (i != 7)
	{
		res = (t_builtin*)malloc(sizeof(t_builtin));
		res->cmd = ft_strdup(builtins[i].cmd);
		res->func = builtins[i].func;
	}
	return (res);
}

int			execute_builtin(t_cmd *cmd, t_env *env,
							int (*func)(t_cmd *, t_env *))
{
	int		ret;

	cmd->fd_out = STDOUT_FILENO;
	cmd->fd_in = STDIN_FILENO;
	if (cmd->pipe_status == true)
	{
		if (pipe(cmd->pipe) < 0)
		{
			ft_error("pipe", NULL, "failed"); // strerror(errno)
			return (1);
		}
		cmd->fd_out = cmd->pipe[WRITE_END];
		//cmd->fd_in = cmd->pipe[READ_END];
	}
	if (cmd->lst_out_red != NULL)
		cmd->fd_out = open_output_redirect(cmd);
	if (cmd->redir_in != NULL)
		cmd->fd_in = open_input_redirect(cmd);
	ret = func(cmd, env);
	if (cmd->pipe_status == true && !cmd->lst_out_red)
		close(cmd->pipe[WRITE_END]);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->pipe_status == true)
		cmd->fd_in = cmd->pipe[READ_END];
	return (ret);
}