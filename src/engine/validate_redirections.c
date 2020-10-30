#include <minishell.h>

static	bool	check_file(const char *pathname, int flags, mode_t mode)
{
	int		fd;

	if ((fd = open(pathname, flags, mode)) < 0)
	{
		ft_error(pathname, NULL, strerror(errno));
		return (false);
	}
	close(fd);
	return (true);
}

bool			validate_output_redirects(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->redir_out != NULL)
	{
		while (cmd->redir_out[i] != NULL)
		{
			if (!check_file(cmd->redir_out[i], O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))
				return (false);
			i++;
		}
	}
	i = 0;
	if (cmd->redir_append_out != NULL)
	{
		while (cmd->redir_append_out[i] != NULL)
		{
			if (!check_file(cmd->redir_append_out[i], O_WRONLY | O_CREAT |
				O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))
				return (false);
			i++;
		}
	}
	return (true);
}

bool			validate_input_redirects(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (cmd->redir_in != NULL)
	{
		tmp = NULL;
		while (cmd->redir_in[i] != NULL)
			i++;
		if (i > 0)
			tmp = cmd->redir_in[i - 1];
		if (tmp != NULL && !check_file(tmp, O_RDONLY, 0))
			return (false);
	}
	return (true);
}
