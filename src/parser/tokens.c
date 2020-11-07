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

#include <minishell.h>

void	parsing(char *token, char **parsed, t_env *env)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\"')
			i += double_quotes(&token[i], parsed, env);
		else if (token[i] == '\'')
			i += single_quotes(&token[i], parsed);
		else if (token[i] == '$')
			i += replace_env(&token[i], env, parsed, 0);
		else if (token[i] == '\\')
		{
			*parsed = add_char(*parsed, token[i + 1]);
			i += 2;
		}
		else
		{
			*parsed = add_char(*parsed, token[i]);
			i++;
		}
	}
}

char	*parse_tokens(char *token, t_env *env)
{
	char	*parsed;

	if (!ft_strcmp(token, ";") || !ft_strcmp(token, "|") ||
		!ft_strcmp(token, ">") || !ft_strcmp(token, ">>") ||
		!ft_strcmp(token, "<"))
		return (ft_strdup(token));
	parsed = ft_strdup("");
	parsing(token, &parsed, env);
	return (parsed);
}
