/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:03:56 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 21:20:14 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_env *env, int fd_out)
{
	while (env != NULL)
	{
		if (env->is_hidden == HIDDEN || env->is_hidden == EXPORT_VIS)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd(env->key, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(env->value, fd_out);
		ft_putendl_fd(fd_out);
		env = env->next;
	}
}

void	print_env_export(t_env *env, int fd_out)
{
	while (env != NULL)
	{
		if (env->is_hidden == HIDDEN || env->is_hidden == ENV_VIS)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(env->key, fd_out);
		if (env->value != NULL)
		{
			ft_putstr_fd("=\"", fd_out);
			ft_putstr_fd(env->value, fd_out);
			ft_putstr_fd("\"", fd_out);
		}
		ft_putendl_fd(fd_out);
		env = env->next;
	}
}
