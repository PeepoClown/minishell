#include <minishell.h>

static	int		check_file(const char *pathname, int flags, mode_t mode)
{
	int		fd;

	if ((fd = open(pathname, flags, mode)) < 0)
	{
		ft_error(pathname, NULL, strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}

// for > and >>
int				validate_output_redirects(t_cmd *cmd) // ret : 0 = ok, 1 = ko
{
	int		i;

	i = 0;
	if (cmd->redir_out != NULL)
		while (cmd->redir_out[i] != NULL)
		{
			if (check_file(cmd->redir_out[i], O_WRONLY | O_CREAT,
				S_IWUSR | S_IWGRP | S_IWOTH) == 1)
				return (1);
			i++;
		}
	if (cmd->redir_append_out != NULL)
		while (cmd->redir_append_out[i] != NULL)
		{
			if (check_file(cmd->redir_append_out[i], O_WRONLY | O_CREAT |
				O_APPEND, S_IWUSR | S_IWGRP | S_IWOTH) == 1)
				return (1);
			i++;
		}
	return (0);
}

// for <
int				validate_input_redirects(t_cmd *cmd) // ret : 0 = ok, 1 = ko
{
	int		i;

	i = 0;
	if (cmd->redir_in != NULL)
		while (cmd->redir_in[i] != NULL)
		{
			if (check_file(cmd->redir_in[i], O_RDONLY,
				S_IRUSR | S_IRGRP | S_IROTH) == 1)
				return (1);
			i++;
		}
	return (0);
}
