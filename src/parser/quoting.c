/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:46:05 by qcraghas          #+#    #+#             */
/*   Updated: 2020/10/25 17:46:28 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void	quotes_multiline(char quote, char **token)
//{
//	char	*s;
//	int		pair;
//	int		i;
//
//	pair = 1;
//	i = -1;
//	s = user_input();
//	while(s[++i] != '\0')
//	{
//		if (s[i] == quote)
//			break ;
//		*token = add_char(*token, s[i]);
//	}
//	while(s[i])
//	{
//		if (s[i] == quote)
//			pair++;
//
//	}
//}

int		double_quotes(char *s, char **token)
{
	int i = 1;

	while(s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			break ;
		}
		if (s[i] == '\\')
		{
			if (s[i + 1] != '\\' && s[i + 1] != '\"' && s[i + 1] != '$')
				*token = add_char(*token, s[i]);
			i++;
		}
		if (!s[i])
			break ;
		*token = add_char(*token, s[i]);
		i++;
	}
	return (i);
}

int		single_quotes(char *s, char **token)
{
	int i = 0;
	if (*s++ == '\'')
		i++;
	while(*s)
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

