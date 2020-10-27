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

#include "parser.h"

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
	int i = 0;
	int close = 0;
	i++;
	s++;
	while(*s)
	{
		if (*s == '\"')
		{
			i++;
			close = 1;
			break ;
		}
//		if (*s == '\\')
//		{
//			i++;
//			s++;
//		}
		if (!*s)
			break ;
		*token = add_char(*token, *s);
		i++;
		s++;
	}
	if (!close)
	{
		write(1, "Bad quoting\n", 12);
		return (i);
	}
	return (i);
}

int		single_quotes(char *s, char **token)
{
	int i = 0;
	int close = 0;
	if (*s++ == '\'')
		i++;
	while(*s)
	{
		close = 0;
		if (*s == '\'')
		{
			i++;
			close = 1;
			break ;
		}
//		if (*s == '\\')
//		{
//			i++;
//			s++;
//		}
		if (!*s)
			break ;
//		if (*s == '$') //metacharacters
//			;
		*token = add_char(*token, *s);
		i++;
		s++;
	}
	if (!close)
	{
		write(1, "Bad quoting\n", 12);
		return (i);
	}
	return (i);
}

