/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:41:36 by qcraghas          #+#    #+#             */
/*   Updated: 2020/10/27 14:41:39 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_quote_pair(char *s, char quote, int *error) //return
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
	write(1, "bash: syntax error near unexpected token `", 42);
	write(1, &unexpected, 1);
	write(1, "'\n", 2);
	return (1);
}

int unexpected_eof(char match_quote)
{
	write(1, GRN, 6);
	write(1, "bash: unexpected EOF while looking for matching `", 49);
	write(1, &match_quote, 1);
	write(1, "\"", 1);
	write(1, NRM, 6);
	write(1, "\n", 1);
	return (1);
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

	if (s[lexer->i] == '\'' || s[lexer->i] == '\"') //"token" -> check_quote: returns 7 ->
	{
		if (s[lexer->i - 1] == ' ')
			*current_token = combine_tokens(*current_token, '\n');
		lexer->match_quote = s[lexer->i]; //current quote
		lexer->token_len = check_quote_pair(&s[lexer->i], s[lexer->i], &lexer->error); //len of string + 2 quotes
		if (lexer->error) //free current token
			return (unexpected_eof(lexer->match_quote));
		quote_token = ft_substr(s, lexer->i, lexer->token_len); //string from position after first (quote) minus 2 quotes
		if (lexer->token_len > 1)
		{
			*current_token = ft_strjoin(*current_token, quote_token);
		}
		free(quote_token);
		quote_token = NULL;
		lexer->i += lexer->token_len; //move string to the char after the pair quote
	}
	return (0);
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
	if (s[lexer->i] == ';' || s[lexer->i] == '|') //'cmd ;    ' could be not valid!
		return (unexpected_token(lexer->unexp_token));
	if (s[lexer->i] == '\0')
		*current_token = combine_tokens(*current_token, '\n');
	if (s[lexer->i])
	{
		*current_token = combine_tokens(*current_token, lexer->unexp_token);
		*current_token = combine_tokens(*current_token, '\n');
	}
	return (0);
}

int		token_redirects(t_lexer *lexer, char *s, char **current_token)
{
	char	*token;

	token = NULL;
	lexer->unexp_token = s[lexer->i];
	if (s[lexer->i - 1] != ' ')
		*current_token = combine_tokens(*current_token, '\n');
	while (s[lexer->i] == lexer->unexp_token)
	{
		token = combine_tokens(token, lexer->unexp_token);
		lexer->i++;
	}
	printf("current redirect token %s\n", token);
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") || !ft_strcmp(token, ">>"))
	{
		token = combine_tokens(token, '\n');
		*current_token = ft_strjoin(*current_token, token);
		return (0);
	}
	return (unexpected_token(lexer->unexp_token));
}

char	**lexer(char *s, t_lexer *lexer)
{
	char	*current_token;

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
		if (s[lexer->i] == '\'' || s[lexer->i] == '\"') //"token" -> check_quote: returns 7 ->
		{
			if (token_quotes(lexer, s, &current_token))
				return (NULL);
		}
		else if (s[lexer->i] == ';' || s[lexer->i] == '|')
		{
			if (token_separators(lexer, s, &current_token))
				return (NULL);
		}
		else if (s[lexer->i] == '>' || s[lexer->i] == '<')
		{
			if (token_redirects(lexer, s, &current_token))
				return (NULL);
		}
		else if(s[lexer->i] == '\\')
		{
			current_token = combine_tokens(current_token, s[lexer->i]);
			lexer->i++;
			if (s[lexer->i])
				current_token = combine_tokens(current_token, s[lexer->i]);
			else
				break ;
			lexer->i++;
		}
		else if (s[lexer->i] == ' ')
		{
			lexer->i += skip_spaces(&s[lexer->i]);
			if (s[lexer->i])
				current_token = combine_tokens(current_token, '\n');
		}
		else
		{
			current_token = combine_tokens(current_token, s[lexer->i]);
			lexer->i++;
		}
	}
	write(1, "end of lexer\n", 13);
	int b;
	char **new = ft_split(current_token, '\n');
	printf("each token:\n");
	b = -1;
	while(new[++b] != NULL)
	{
		printf("token number %02d --> |%s%s%s|\n", b + 1, GRN, new[b], NRM);
	}
	return (new);
}


