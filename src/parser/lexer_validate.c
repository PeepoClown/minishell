/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:53:03 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 16:53:05 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		token_quotes(t_lexer *lexer, char *s, char **current_token)
{
	char	*quote_token;
	char	*tmp;

	if (s[lexer->i] == '\'' || s[lexer->i] == '\"')
	{
		if (s[lexer->i - 1] == ' ')
			*current_token = combine_tokens(*current_token, '\n');
		lexer->match_quote = s[lexer->i];
		lexer->token_len = quote_pair(&s[lexer->i], s[lexer->i], &lexer->error);
		if (lexer->error)
			return (unexpected_eof(lexer->match_quote));
		quote_token = ft_substr(s, lexer->i, lexer->token_len);
		if (lexer->token_len > 1)
		{
			tmp = *current_token;
			*current_token = ft_strjoin(*current_token, quote_token);
			free(tmp);
		}
		free(quote_token);
		quote_token = NULL;
		lexer->i += lexer->token_len;
	}
	return (1);
}

int		token_separators(t_lexer *lex, char *s, char **current_token)
{
	lex->unexp_token = s[lex->i];
	if (s[lex->i - 1] != ' ')
		*current_token = combine_tokens(*current_token, '\n');
	if (s[lex->i - 2] == lex->unexp_token && !ft_strchr("\'\"", s[lex->i - 1]))
		return (unexpected_token(lex->unexp_token));
	if (s[lex->i - 1] == lex->unexp_token)
		return (unexpected_token(lex->unexp_token));
	lex->i = spaces(&s[lex->i]) ? lex->i + spaces(&s[lex->i]) : lex->i + 1;
	if (s[lex->i] == ';' || s[lex->i] == '|')
		return (unexpected_token(lex->unexp_token));
	if (s[lex->i] == '\0')
		*current_token = combine_tokens(*current_token, '\n');
	if (s[lex->i])
	{
		*current_token = combine_tokens(*current_token, lex->unexp_token);
		*current_token = combine_tokens(*current_token, '\n');
	}
	return (1);
}

int		token_redirects(t_lexer *lexer, char *s, char **current_token)
{
	char	*t;
	char	*tmp;

	t = NULL;
	lexer->unexp_token = s[lexer->i];
	if (s[lexer->i - 1] != ' ')
		*current_token = combine_tokens(*current_token, '\n');
	while (s[lexer->i] == lexer->unexp_token)
	{
		t = combine_tokens(t, lexer->unexp_token);
		lexer->i++;
	}
	if (!ft_strcmp(t, "<") || !ft_strcmp(t, ">") || !ft_strcmp(t, ">>"))
	{
		t = combine_tokens(t, '\n');
		tmp = *current_token;
		*current_token = ft_strjoin(*current_token, t);
		free(t);
		free(tmp);
		tmp = NULL;
		return (1);
	}
	free(t);
	return (unexpected_token(lexer->unexp_token));
}

int		lexer_backslash(char *s, t_lexer *lexer, char **current_token)
{
	if (!s[lexer->i + 1])
	{
		return (unexpected_token('\\'));
	}
	*current_token = combine_tokens(*current_token, s[lexer->i]);
	lexer->i++;
	if (s[lexer->i])
		*current_token = combine_tokens(*current_token, s[lexer->i]);
	lexer->i++;
	return (1);
}

void	lexer_env(t_lexer *lexer, char *s, char **current_token)
{
	*current_token = combine_tokens(*current_token, s[lexer->i]);
	*current_token = combine_tokens(*current_token, s[lexer->i + 1]);
	lexer->i += 2;
	while (s[lexer->i] && s[lexer->i] != '\'')
	{
		*current_token = combine_tokens(*current_token, s[lexer->i]);
		if (s[lexer->i] == '\\' && ft_strchr("nt\\\'", s[lexer->i + 1]))
		{
			*current_token = combine_tokens(*current_token, s[lexer->i + 1]);
			lexer->i++;
		}
		lexer->i++;
	}
	if (s[lexer->i])
	{
		*current_token = combine_tokens(*current_token, s[lexer->i]);
		lexer->i++;
	}
	*current_token = combine_tokens(*current_token, '\n');
}
