/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:41:36 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/06 19:10:02 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		check_quote_pair(char *s, char quote, int *error)
{
	int i = 1;

	*error = 1;
	if (!s[i])
		*error = 1;
	if (s[i] == quote)
	{
		*error = 0;
		return (i + 1);
	}
	while(s[i] != quote && s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] == '\"')
			i += 2;
		else
			i++;
		if (s[i] == quote)
			*error = 0;
	}
	return (i + 1);
}

int		skip_spaces(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (i + 1);
	while(s[i] == ' ')
		i++;
	return(i);
}

int unexpected_token(char unexpected)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, &unexpected, 1);
	write(2, "'\n", 2);
	g_status = 258;
	return (0);
}

int unexpected_eof(char match_quote)
{
	write(2, "bash: unexpected EOF while looking for matching `", 49);
	write(2, &match_quote, 1);
	write(2, "\"\n", 2);
	g_status = 258;
	return (0);
}


void	lexer_init(t_lexer *lexer)
{
	lexer->i = 0;
	lexer->error = 0;
	lexer->token_len = 0;
}

int		token_quotes(t_lexer *lexer, char *s, char **current_token)
{
	char	*quote_token;
	char	*tmp;

	if (s[lexer->i] == '\'' || s[lexer->i] == '\"')
	{
		if (s[lexer->i - 1] == ' ')
			*current_token = combine_tokens(*current_token, '\n');
		lexer->match_quote = s[lexer->i];
		lexer->token_len = check_quote_pair(&s[lexer->i], s[lexer->i], &lexer->error);
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


int		token_separators(t_lexer *lexer, char *s, char **current_token)
{
	lexer->unexp_token = s[lexer->i];
	if (s[lexer->i - 1] != ' ')
		*current_token = combine_tokens(*current_token, '\n');
	if (s[lexer->i - 2] == lexer->unexp_token && !ft_strchr("\'\"", s[lexer->i - 1]))
		return (unexpected_token(lexer->unexp_token));
	if (s[lexer->i - 1] == lexer->unexp_token)
		return (unexpected_token(lexer->unexp_token));
	lexer->i = skip_spaces(&s[lexer->i]) ? lexer->i + skip_spaces(&s[lexer->i]) : lexer->i + 1;
	if (s[lexer->i] == ';' || s[lexer->i] == '|')
		return (unexpected_token(lexer->unexp_token));
	if (s[lexer->i] == '\0')
		*current_token = combine_tokens(*current_token, '\n');
	if (s[lexer->i])
	{
		*current_token = combine_tokens(*current_token, lexer->unexp_token);
		*current_token = combine_tokens(*current_token, '\n');
	}
	return (1);
}

int		token_redirects(t_lexer *lexer, char *s, char **current_token)
{
	char	*token;
	char	*tmp;

	token = NULL;
	lexer->unexp_token = s[lexer->i];
	if (s[lexer->i - 1] != ' ')
		*current_token = combine_tokens(*current_token, '\n');
	while (s[lexer->i] == lexer->unexp_token)
	{
		token = combine_tokens(token, lexer->unexp_token);
		lexer->i++;
	}
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") || !ft_strcmp(token, ">>"))
	{
		token = combine_tokens(token, '\n');
		tmp = *current_token;
		*current_token = ft_strjoin(*current_token, token);
		free(token);
		free(tmp);
		tmp = NULL;
		return (1);
	}
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
	else if(s[lexer->i] == '\\')
		status = lexer_backslash(s, lexer, current_token);
	else if (s[lexer->i] == ' ')
	{
		lexer->i += skip_spaces(&s[lexer->i]);
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

char	**lexer(char *s, t_lexer *lexer)
{
	char	*current_token;
	char	**parsed;

	lexer_init(lexer);
	current_token = NULL;
	lexer->i = skip_spaces(s);
	if (s[lexer->i] == ';' || s[lexer->i] == '|')
	{
		unexpected_token(s[lexer->i]);
		return (NULL);
	}
	while(s[lexer->i])
	{
		lexer->token_len = 0;
		if (!lexer_symbols(s, lexer, &current_token))
			return (NULL);
	}
	if (!current_token)
		return (NULL);
	parsed = ft_split(current_token, '\n');
	free(current_token);
	current_token = NULL;
	return (parsed);
}


