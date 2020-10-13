#include "../minishell.h"

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
void	ft_error(char *cmd, char *error, char *desc);

int		ft_cd(t_cmd *cmd, int fd_out, char *home_path)
{
	char	path[PATH_MAX];
	char	*dest_path;

	fd_out = 1;
	dest_path = (ft_strcmp(cmd->args[0], "") == 0)
		? home_path
		: cmd->args[0];
	if ((chdir(dest_path) == -1))
	{
		ft_error(cmd->name, cmd->args[0], strerror(errno));
		return (1);
	}
	return (0);
}
