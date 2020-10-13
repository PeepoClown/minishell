#include "../minishell.h"

// env dictionary must be sorted!!!

int		ft_find_first_of(const char *str, char sym);
size_t	ft_strlen(const char *str);
void	ft_error(char *cmd, char *error, char *desc);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *str);

void	ft_putnstr_fd(const char *str, int start, int length, int fd)
{
	int		i;

	i = start;
	while ((str[i] != '\0') && (i < length))
	{
		write(fd, &(str[i]), 1);
		i++;
	}
}

void	print_env_export(int fd_out, char **env)
{
	int		delim_pos;

	while (*env != NULL)
	{
		write(fd_out, "declare -x ", 12);
		delim_pos = ft_find_first_of(*env, '=');
		ft_putnstr_fd(*env, 0, delim_pos, fd_out);
		write(1, "=", 1);
		write(1, "\"", 1);
		ft_putnstr_fd(*env, delim_pos + 1,
			ft_strlen(*env), fd_out);
		write(1, "\"", 1);
		write(1, "\n", 1);
		env++;
	}
}

char	**sort_env(char **env, int env_count)
{
	int		i;
	int		j;
	int		k;
	int		min_id;
	char	*tmp;
	//char	**matrix;
	
	i = 0;
	//matrix = (char**)malloc(sizeof(char*) * (env_count + 1));
	while (i < env_count - 1)
	{
		min_id = i;
		j = i + 1;
		while (j < env_count)
		{
			if (ft_strcmp(env[min_id], env[j]) > 0)
				min_id = j;
			j++;
		}
		if (min_id != i)
		{
			tmp = ft_strdup(env[i]);
			env[i] = ft_strdup(env[min_id]);
			env[min_id] = tmp;
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

// one more - oldpwd

int		ft_export(t_cmd *cmd, int fd_out, char **env)
{
	int env_count = 0;
	char	**tmp_env = env;
	while (tmp_env[env_count] != NULL)
		env_count++;
	char **env_export = env;
	// = sort_env(env, env_count);
	while (*env_export != NULL)
	{
		printf("%s\n", *env_export);
		env_export++;
	}
	//print_env_export(fd_out, env_export);
	// if (cmd->args_count == 0)
	// {

	// }
	return (0);
}
