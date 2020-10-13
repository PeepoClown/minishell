#include "../minishell.h"

size_t	ft_strlen(const char *str);
void	ft_error(char *cmd, char *error, char *desc);

int		ft_pwd(t_cmd *cmd, int fd_out)
{
	char	path[PATH_MAX];

	if (!(getcwd(path, PATH_MAX)))
	{
		ft_error(cmd->name, NULL, strerror(errno));
		return (1);
	}
	write(fd_out, path, ft_strlen(path));
	write(fd_out, "\n", 1);
	return (0);
}
