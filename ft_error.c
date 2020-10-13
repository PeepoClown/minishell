#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t count;

	count = 0;
	while (*(str + count))
		count++;
	return (count);
}

void	ft_error(char *cmd, char *error, char *desc)
{
	write(2, "shell: ", 8);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 3);
	if (error)
	{
		write(2, error, ft_strlen(error));
		write(2, ": ", 3);
	}
	write(2, desc, ft_strlen(desc));
	write(2, "\n", 1);
}