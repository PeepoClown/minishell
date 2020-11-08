/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:02:14 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/08 10:47:05 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	on_sig_int(void)
{
	if (g_pid > 0)
		ft_putendl_fd(1);
	else if (g_pid == 0)
	{
		g_status = 1;
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putendl_fd(1);
		display_prompt();
		g_input_start = false;
	}
}

static	void	on_sig_quit(void)
{
	if (g_input_start == true)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void			signals_handler(int sig)
{
	if (sig == SIGINT)
		on_sig_int();
	else if (sig == SIGQUIT)
		on_sig_quit();
	else
		return ;
}
