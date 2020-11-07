/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:01:45 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 19:13:05 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	set_builtin(int *i, const char *cmd_name,
								const t_builtin *builtins)
{
	while (*i < 7)
	{
		if (ft_strcmp(cmd_name, builtins[*i].cmd) == 0)
			break ;
		(*i)++;
	}
}

t_builtin		*get_builtin(const char *cmd_name)
{
	const t_builtin	builtins[7] = {
		{ "echo", (int (*)(void *, struct s_env *))ft_echo },
		{ "cd", (int (*)(void *, struct s_env *))ft_cd },
		{ "pwd", (int (*)(void *, struct s_env *))ft_pwd },
		{ "export", (int (*)(void *, struct s_env *))ft_export },
		{ "env", (int (*)(void *, struct s_env *))ft_env },
		{ "unset", (int (*)(void *, struct s_env *))ft_unset },
		{ "exit", (int (*)(void *, struct s_env *))ft_exit } };
	t_builtin		*res;
	int				i;

	i = 0;
	set_builtin(&i, cmd_name, builtins);
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
