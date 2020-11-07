/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:00:56 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:00:57 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_echo(t_cmd *cmd, t_env *env)
{
	bool	nl_flag;
	int		i;

	env = NULL;
	i = 0;
	if (*(cmd->args) == NULL)
	{
		ft_putendl_fd(cmd->fd_out);
		return (0);
	}
	while(!ft_strcmp(cmd->args[i], "-n"))
		i++;
	nl_flag = i != 0 ? false : true;
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], cmd->fd_out);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", cmd->fd_out);
		i++;
	}
	if (nl_flag)
		ft_putendl_fd(cmd->fd_out);
	return (0);
}
