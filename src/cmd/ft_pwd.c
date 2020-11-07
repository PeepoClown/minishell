/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:01:14 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:01:15 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_pwd(t_cmd *cmd, t_env *env)
{
	char	path[PATH_MAX];

	env = NULL;
	if (!getcwd(path, PATH_MAX))
	{
		ft_error("pwd", NULL, strerror(errno));
		return (1);
	}
	ft_putstr_fd(path, cmd->fd_out);
	ft_putendl_fd(cmd->fd_out);
	return (0);
}
