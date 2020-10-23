#include <minishell.h>

char	*get_programm_path(const char *cmd, char **paths)
{
	struct stat stat_buff;
	char		*res;
	int			i;
	char		*tmp1;
	char		*tmp2;

	i = 0;
	res = NULL;
	while (paths[i] != NULL)
	{
		tmp1 = ft_strjoin(paths[i], "/");
		tmp2 = tmp1;
		tmp1 = ft_strjoin(tmp1, cmd);
		free(tmp2);
		stat(tmp1, &stat_buff);
		if (S_ISREG(stat_buff.st_mode) == true)
		{
			res = tmp1;
			break ;
		}
		free(tmp1);
		i++;
	}
	return (res);
}

char	**get_args_matrix(const char *cmd, char **args)
{
	char	**args_matrix;
	int		args_count;
	int		i;

	args_count = 0;
	while (args[args_count] != NULL)
		args_count++;
	if (!(args_matrix = (char**)malloc(sizeof(char*) * (args_count + 2))))
		return (NULL);
	i = 0;
	args_matrix[i] = ft_strdup(cmd);
	i++;
	while (i < (args_count + 1))
	{
		args_matrix[i] = ft_strdup(args[i - 1]);
		i++;
	}
	args_matrix[i] = NULL;
	return (args_matrix);
}
