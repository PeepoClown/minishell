/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:41:36 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/06 21:48:56 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		spaces(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (i + 1);
	while (s[i] == ' ')
		i++;
	return (i);
}

void	lexer_init(t_lexer *lexer)
{
	lexer->i = 0;
	lexer->error = 0;
	lexer->token_len = 0;
}

int		lexer_symbols(char *s, t_lexer *lexer, char **current_token)
{
	int		status;

	status = 1;
	if (s[lexer->i] == '\'' || s[lexer->i] == '\"')
		status = token_quotes(lexer, s, current_token);
	else if (s[lexer->i] == ';' || s[lexer->i] == '|')
		status = token_separators(lexer, s, current_token);
	else if (s[lexer->i] == '>' || s[lexer->i] == '<')
		status = token_redirects(lexer, s, current_token);
	else if (s[lexer->i] == '\\')
		status = lexer_backslash(s, lexer, current_token);
	else if (s[lexer->i] == '$' && s[lexer->i + 1] == '\'')
		lexer_env(lexer, s, current_token);
	else if (s[lexer->i] == ' ')
	{
		lexer->i += spaces(&s[lexer->i]);
		if (s[lexer->i])
			*current_token = combine_tokens(*current_token, '\n');
	}
	else
	{
		*current_token = combine_tokens(*current_token, s[lexer->i]);
		lexer->i++;
	}
	return (status);
}

char	**check_last_elem(char *current_token)
{
	char	**parsed;
	int		i;

	parsed = ft_split(current_token, '\n');
	i = array_size(parsed);
	if (i > 0 && (!ft_strcmp(parsed[i - 1], ">") ||
		!ft_strcmp(parsed[i - 1], ">>") ||
		!ft_strcmp(parsed[i - 1], "<")))
	{
		unexpected_redirects();
		free(current_token);
		current_token = NULL;
		ft_remove_char_matrix(parsed);
		return (NULL);
	}
	free(current_token);
	current_token = NULL;
	return (parsed);
}

char	**lexer(char *s, t_lexer *lexer)
{
	char	*current_token;

	lexer_init(lexer);
	current_token = NULL;
	lexer->i = spaces(s);
	if (s[lexer->i] == ';' || s[lexer->i] == '|')
	{
		unexpected_token(s[lexer->i]);
		return (NULL);
	}
	while (s[lexer->i])
	{
		lexer->token_len = 0;
		if (!lexer_symbols(s, lexer, &current_token))
		{
			free(current_token);
			return (NULL);
		}
	}
	if (!current_token)
		return (NULL);
	return (check_last_elem(current_token));
}
