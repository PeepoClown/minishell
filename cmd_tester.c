#include "minishell.h"

int		ft_pwd(t_cmd *cmd, int fd_out);
int		ft_echo(t_cmd *cmd, int fd_out);
int		ft_cd(t_cmd *cmd, int fd_out, char *home_path);
int		ft_export(t_cmd *cmd, int fd_out, char **env);

size_t	ft_strlen(const char *str)
{
	size_t count;

	count = 0;
	while (*(str + count))
		count++;
	return (count);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*copy;

	copy = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(str))
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int		ft_find_first_of(const char *str, char sym)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sym)
			return (i);
		i++;
	}
	return (-1);
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

int		main(int argc, char **argv, char **env)
{
	t_cmd cmd;
	int res;
	// cmd.name = "pwd";
	// cmd.args = NULL;
	// cmd.args_count = 0;
	// int fd = open(argv[1], O_RDWR);
	// res = ft_pwd(&cmd, 1);
	// printf("returned : %d\n", res);
	// close(fd);
	// t_cmd cmd;
	// cmd.name = "echo";
	// char *args[] = {"-n", "sad", "sadasd  asdas|", NULL};
	// cmd.args = args;
	// cmd.args_count = 3;
	// int fd = open(argv[1], O_RDWR);
	// int res = ft_echo(&cmd, 1);
	// printf("returned : %d\n", res);
	// close(fd);
	// cmd.name = "cd";
	// char *args[] = { "/GSDsdf" };
	// cmd.args = args;
	// cmd.args_count = 0;
	//int fd = open(argv[1], O_RDWR);
	// res = ft_cd(&cmd, 1, "/Users/wupdegra");
	// printf("returned : %d\n", res);
	// char path[4096];
	// printf("%s\n", getcwd(path, 4096));
	//close(fd);
	cmd.name = "export";
	cmd.args = NULL;
	cmd.args_count = 0;
	//int fd = open(argv[1], O_RDWR);
	res = ft_export(&cmd, 1, env);
	printf("returned : %d\n", res);
	//close(fd);
	return (0);
}