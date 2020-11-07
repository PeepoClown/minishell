/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:46:05 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/06 22:17:09 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	d_quotes(char *s, char **token, t_env *env, int *i)
{
	while (s[*i])
	{
		if (s[*i] == '\"')
		{
			(*i)++;
			break ;
		}
		if (s[*i] == '$')
		{
			(*i) += replace_env(&s[*i], env, token, 1);
			continue ;
		}
		if (s[*i] == '\\')
		{
			if (s[*i + 1] != '\\' && s[*i + 1] != '\"' && s[*i + 1] != '$')
				*token = add_char(*token, s[*i]);
			(*i)++;
		}
		if (!s[*i])
			break ;
		*token = add_char(*token, s[*i]);
		(*i)++;
	}
}

int		double_quotes(char *s, char **token, t_env *env)
{
	int i;

	i = 1;
	d_quotes(s, token, env, &i);
	return (i);
}

int		single_quotes(char *s, char **token)
{
	int i;

	i = 0;
	if (*s++ == '\'')
		i++;
	while (*s)
	{
		if (*s == '\'')
		{
			i++;
			break ;
		}
		if (!*s)
			break ;
		*token = add_char(*token, *s);
		i++;
		s++;
	}
	return (i);
}
