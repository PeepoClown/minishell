#include "minishell.h"

char	*concat_env(t_env *env)
{
	char	*tmp;
	char	*res;

	res = ft_strdup(env->key);
	tmp = res;
	res = ft_strjoin(res, "=");
	free(tmp);
	tmp = res;
	res = ft_strjoin(res, env->value);
	free(tmp);
	return (res);
}

char	**get_env(t_env *env)
{
	char	**res;
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	res = (char**)malloc(sizeof(char*) * (count + 1));
	count = 0;
	tmp = env;
	while (tmp != NULL)
	{
		res[count] = concat_env(tmp);
		tmp = tmp->next;
		count++;
	}
	res[count] = NULL;
	return (res);
}

void	print_vars(char **env_vars)
{
	while (*env_vars != NULL)
	{
		printf("%s\n", *env_vars);
		env_vars++;
	}
}

char	*get_path(char *cmd, char *path)
{
	char		**paths;
	char		*res;
	char		*tmp;
	int			i;
	struct stat	buff;

	i = 0;
	res = NULL;
	paths = ft_split(path, ':');
	while (paths[i] != NULL)
	{
		paths[i] = ft_strjoin(paths[i], "/");
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i],cmd);
		free(tmp);
		stat(paths[i], &buff);
		if (S_ISREG(buff.st_mode) == true)
		{
			res = paths[i];
			break ;
		}
		i++;
	}
	i = 0;
	while (paths[i] != NULL)
	{
		if (ft_strcmp(paths[i], res))
			free(paths[i]);
		i++;
	}
	free(paths);
	return (res);
}

char	**get_args(char *cmd, char **args)
{
	int		args_count;
	char	**res;
	int		i;

	args_count = 0;
	while (args[args_count] != NULL)
		args_count++;
	res = (char**)malloc(sizeof(char*) * (args_count + 2));
	i = 0;
	res[i] = ft_strdup(cmd);
	i++;
	printf("programm name : %s\n", res[0]);
	while (i < (args_count + 1))
	{
		res[i] = ft_strdup(args[i - 1]);
		printf("%d param : %s\n", i, res[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int		execute(t_cmd *cmd, t_env *env, char **envp)
{
	pid_t	pid;
	char	**env_vars;
	char	*path;
	int		ret;
	char	**args;

	pid = fork();
	// if (pid < 0)
	// 	error_cmd("fork", NULL, "failed");
	if (pid > 0)
		wait(&pid);
	else
	{
		env_vars = get_env(env);
		path = get_path(cmd->name, get_env_value(env, "PATH"));
		//print_vars(env_vars);
		args = get_args(path, cmd->args);
		printf("Path to %s : %s\n", cmd->name, path);
		execve(path, args, envp);
		if (ret < 0)
			error_cmd("execve", NULL, "no such command");
		//exit(ret);
	}
	return (0);
}
