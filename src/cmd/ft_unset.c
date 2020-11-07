/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:01:17 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:01:18 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	arg_valid(const char *arg)
{
	if (!ft_isalpha(*arg) && !(*arg == '_'))
		return (false);
	arg++;
	while (*arg != '\0')
	{
		if (!ft_isalnum(*arg) && !(*arg == '_'))
			return (false);
		arg++;
	}
	return (true);
}

int				ft_unset(t_cmd *cmd, t_env *env)
{
	int		ret;
	int		i;

	if (!env)
		return (errno = 1);
	ret = 0;
	i = 0;
	while (cmd->args[i] != NULL)
	{
		if (arg_valid(cmd->args[i]))
			del_env(&env, cmd->args[i]);
		else
		{
			ft_error("unset", cmd->args[i], "not a valid identifier");
			ret = 1;
		}
		i++;
	}
	return (ret);
}
