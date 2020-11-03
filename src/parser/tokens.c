/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:38:08 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/03 19:38:10 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parsing(char *token)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup("");
	if (!ft_strcmp(token, ";") || !ft_strcmp(token, "|") ||
		!ft_strcmp(token, ">") || !ft_strcmp(token, ">>") ||
		!ft_strcmp(token, "<"))
		return (ft_strdup(token));
	else
		while(token[i])
		{
			if (token[i] == '\"')
				i += double_quotes(&token[i], &s);
			else if (token[i] == '\'')
				i += single_quotes(&token[i], &s);
			else if (token[i] == '\\')
			{
				s = add_char(s, token[i + 1]);
				i += 2;
			}
			else
			{
				s = add_char(s, token[i]);
				i++;
			}
		}
	return (s);
}

char	*parse_tokens(char *token)
{
	char	*parsed;
	int		i;

	i = -1;
	if (!(parsed = parsing(token)))
		return (NULL);
//		free(tmp[i]);
//		tmp[i] = NULL;
//	free(tmp);
//	tmp = NULL;
	return (parsed);
}
