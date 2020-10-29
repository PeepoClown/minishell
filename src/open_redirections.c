#include <minishell.h>

static	int		open_output_append_redirect(t_cmd *cmd)
{
	int		fd;

	if ((fd = open(cmd->last_out_redir, O_WRONLY | O_APPEND)) < 0)
	{
		ft_error(NULL, NULL, "can't redirect to standart output");
		return (STDOUT_FILENO);
	}
	return (fd);
}

int				open_output_redirect(t_cmd *cmd, int fd_out, int fd_in)
{
	int		fd;

	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (!cmd->is_last_out_redir_default)
		return (open_output_append_redirect(cmd));
	if ((fd = open(cmd->last_out_redir, O_WRONLY | O_TRUNC)) < 0)
	{
		ft_error(NULL, NULL, "can't redirect to standart output");
		return (STDOUT_FILENO);
	}
	return (fd);
}

int				open_input_redirect(t_cmd *cmd, int fd_out, int fd_in)
{
	int		fd;
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (cmd->redir_in[i] != NULL)
		i++;
	if (i > 0)
		tmp = cmd->redir_in[i - 1];
	if (tmp != NULL)
	{
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if ((fd = open(tmp, O_RDONLY)) < 0)
		{
			ft_error(NULL, NULL, "can't redirect to standart input");
			return (STDIN_FILENO);
		}
		return (fd);
	}
	return (fd_in);
}
