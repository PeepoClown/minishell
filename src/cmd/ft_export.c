/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:01:10 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:01:11 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	bool	arg_valid(const char *arg)
{
	if (!ft_isalpha(*arg) && !(*arg == '_'))
		return (false);
	arg++;
	while (*arg != '\0')
	{
		if (*arg == '=')
			break ;
		if (!ft_isalnum(*arg) && !(*arg == '_'))
			return (false);
		arg++;
	}
	return (true);
}

static	void	empty_args_export(t_cmd *cmd, t_env *env)
{
	t_env	*copy;

	copy = copy_env(env);
	sort_env(&copy);
	print_env_export(copy, cmd->fd_out);
	g_is_copy_rm = true;
	remove_env(&copy);
	g_is_copy_rm = false;
}

int				ft_export(t_cmd *cmd, t_env *env)
{
	int		ret;
	int		i;

	if (!env)
		return (errno = 1);
	ret = 0;
	i = 0;
	if (cmd->args[i] == NULL)
	{
		empty_args_export(cmd, env);
		return (ret);
	}
	while (cmd->args[i] != NULL)
	{
		if (arg_valid(cmd->args[i]))
			add_to_env(env, cmd->args[i]);
		else
		{
			ft_error("export", cmd->args[i], "not a valid identifier");
			ret = 1;
		}
		i++;
	}
	return (ret);
}
