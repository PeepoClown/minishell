#include <minishell.h>

static	int		open_output_append_redirect(t_cmd *cmd)
{
	int		fd;

	if ((fd = open(cmd->lst_out_red, O_WRONLY | O_APPEND)) < 0)
	{
		ft_error(NULL, NULL, "can't redirect to standart output");
		return (STDOUT_FILENO);
	}
	return (fd);
}

int				open_output_redirect(t_cmd *cmd)
{
	int		fd;

	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (!cmd->is_lst_out_red_append)
		return (open_output_append_redirect(cmd));
	if ((fd = open(cmd->lst_out_red, O_WRONLY | O_TRUNC)) < 0)
	{
		ft_error(NULL, NULL, "can't redirect to standart output");
		return (STDOUT_FILENO);
	}
	return (fd);
}

int				open_input_redirect(t_cmd *cmd)
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
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if ((fd = open(tmp, O_RDONLY)) < 0)
		{
			ft_error(NULL, NULL, "can't redirect to standart input");
			return (STDIN_FILENO);
		}
		return (fd);
	}
	return (cmd->fd_in);
}
