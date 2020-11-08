/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:01:07 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/08 19:24:45 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	bool		is_digital_arg(char *arg)
{
	bool	is_sign;

	is_sign = false;
	while (*arg == ' ')
		arg++;
	if (*arg == '-' || *arg == '+')
	{
		is_sign = true;
		++arg;
	}
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			break ;
		is_sign = false;
		arg++;
	}
	while (*arg == ' ')
		arg++;
	if (*arg != '\0')
		return (false);
	return (!is_sign);
}

static long long	validate_exit_code(char *code)
{
	bool	minus;
	char	*num;
	char	*orig;

	minus = false;
	orig = code;
	while (*code == ' ')
		code++;
	if (*code == '-')
	{
		code++;
		minus = true;
	}
	num = ft_strtrim(code, " ");
	if (ft_strlen(num) < 20 && (ft_atoll(num) <= LLONG_MAX ||
		((ft_atoll(num) <= (unsigned long long)(LLONG_MAX) + 1) && minus)))
	{
		free(num);
		return (minus ? ft_atoll(code) * (-1) : ft_atoll(code));
	}
	free(num);
	ft_error("exit", orig, "numeric argument required");
	return (255);
}

int					ft_exit(t_cmd *cmd, t_env *env)
{
	int		ret;
	int		args_count;

	env = NULL;
	ft_putstr_fd(cmd->name, 2);
	ft_putendl_fd(2);
	args_count = 0;
	while (*(cmd->args + args_count) != NULL)
		args_count++;
	if (args_count == 0)
		ret = g_status;
	else if ((!is_digital_arg(*(cmd->args))) & (ret = 255))
		ft_error(cmd->name, *(cmd->args), "numeric argument required");
	else
	{
		if (args_count > 1)
		{
			ft_error(cmd->name, NULL, "too many arguments");
			return (1);
		}
		else
			ret = (unsigned char)validate_exit_code(*(cmd->args));
	}
	remove_prompt_vars(g_user, g_home, g_home_const);
	exit(ret);
}
