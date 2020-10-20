#include <minishell.h>

static	t_builtin	*alloc_builtins(const t_builtin *_builtins)
{
	t_builtin	*builtins;
	int			i;

	builtins = (t_builtin*)malloc(sizeof(t_builtin) * 7);
	i = 0;
	while (i < 7)
	{
		builtins[i].cmd = ft_strdup(_builtins[i].cmd);
		builtins[i].func = _builtins[i].func;
		i++;
	}
	return (builtins);
}

void				remove_builtins(t_builtin *builtins, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		free(builtins[i].cmd);
		i++;
	}
	free(builtins);
}

t_builtin			*get_builtin(const char *cmd_name)
{
	const t_builtin	_builtins[] = { { "echo", ft_echo }, { "cd", ft_cd },
		{ "pwd", ft_pwd }, { "export", ft_export }, { "env", ft_env },
		{ "unset", ft_unset }, { "exit", ft_exit } };
	t_builtin		*builtins;
	t_builtin		*res;
	int 			i;

	builtins = alloc_builtins(_builtins);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd_name, builtins[i].cmd) == 0)
			break ;
		i++;
	}
	if (i != 7)
	{
		res = (t_builtin*)malloc(sizeof(t_builtin));
		res->cmd = ft_strdup(builtins[i].cmd);
		res->func = builtins[i].func;
	}
	remove_builtins(builtins, 7);
	return ((i != 7) ? res : NULL);
}
