#include <minishell.h>

t_builtin	*get_builtin(const char *cmd_name)
{
	const t_builtin	builtins[7] = { { "echo", ft_echo }, { "cd", ft_cd },
		{ "pwd", ft_pwd }, { "export", ft_export }, { "env", ft_env },
		{ "unset", ft_unset }, { "exit", ft_exit } };
	t_builtin		*res;
	int				i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd_name, builtins[i].cmd) == 0)
			break ;
		i++;
	}
	res = NULL;
	if (i != 7)
	{
		if (!(res = (t_builtin*)malloc(sizeof(t_builtin))))
			return (NULL);
		res->cmd = ft_strdup(builtins[i].cmd);
		res->func = builtins[i].func;
	}
	return (res);
}
