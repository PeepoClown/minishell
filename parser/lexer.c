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

#include "../include/minishell.h"

int		check_quote_pair(char *s, char quote, int *error) //return
{
	int i = 1;

	*error = 1;
	if (!s[i])
		error = 0; //1?
	if (s[i] == quote)
	{
		*error = 0;
		return (i + 1);
	}
	while(s[i] != quote && s[i] != '\0')
	{
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
	write(1, "bash: unexpected EOF while looking for matching ", 48); //not matching quotes
	write(1, &match_quote, 1);
	write(1, "\n", 1);
	return (1);
}


void	lexer_init(t_lexer *lexer)
{
	lexer->i = 0;
	lexer->error = 0;
	lexer->token_len = 0;
	if (!(lexer->tokens = (char **)malloc(sizeof(char *))))
		exit (1);
	lexer->tokens[0] = NULL;
}

int		lexer(char *s)
{
	t_lexer	lexer;
	int		num_of_tokens;
	char	*current_token;
	char	*quote_token;

	lexer_init(&lexer);
	num_of_tokens = 0;
	current_token = NULL;
	lexer.i = skip_spaces(s);
	if (s[lexer.i] == ';' || s[lexer.i] == '|')
		return (unexpected_token(s[lexer.i]));
	while(s[lexer.i])
	{
		lexer.token_len = 0;
		if (s[lexer.i] == '\'' || s[lexer.i] == '\"') //"token" -> check_quote: returns 7 ->
		{
			if (s[lexer.i - 1] == ' ')
				current_token = combine_tokens(current_token, '\n');
			lexer.match_quote = s[lexer.i]; //current quote
			lexer.token_len = check_quote_pair(&s[lexer.i], s[lexer.i], &lexer.error); //len of string + 2 quotes
			if (lexer.error) //free current token
				return (unexpected_eof(lexer.match_quote));
			quote_token = ft_substr(s, lexer.i, lexer.token_len); //string from position after first (quote) minus 2 quotes
			if (lexer.token_len > 1)
			{
				current_token = ft_strjoin(current_token, quote_token);
//				current_token = combine_tokens(current_token, '\n');
			}
			free(quote_token);
			quote_token = NULL;
			lexer.i += lexer.token_len; //move string to the char after the pair quote
		}
		else if (s[lexer.i] == ';' || s[lexer.i] == '|')
		{
			if (s[lexer.i - 1] != ' ')
				current_token = combine_tokens(current_token, '\n');
			lexer.unexp_token = s[lexer.i];
			lexer.i = skip_spaces(&s[lexer.i]) ? lexer.i + skip_spaces(&s[lexer.i]) : lexer.i + 1;
			if (s[lexer.i] == ';' || s[lexer.i] == '|') //'cmd ;    ' could be not valid!
				return (unexpected_token(lexer.unexp_token));
			if (s[lexer.i] == '\0')
				current_token = combine_tokens(current_token, '\n');
			if (s[lexer.i])
			{
				current_token = combine_tokens(current_token, lexer.unexp_token);
				current_token = combine_tokens(current_token, '\n');
			}
		}
		else if (s[lexer.i] == '>' || s[lexer.i] == '<')
		{
			lexer.unexp_token = s[lexer.i];
			if (s[lexer.i - 1] != ' ')
				current_token = combine_tokens(current_token, '\n');
			while (s[lexer.i] == lexer.unexp_token)
			{
				current_token = combine_tokens(current_token, lexer.unexp_token);
				lexer.i++;
			}
			current_token = combine_tokens(current_token, '\n');
		}
		else if (s[lexer.i] == ' ')
		{
			lexer.i += skip_spaces(&s[lexer.i]);
			if (s[lexer.i])
				current_token = combine_tokens(current_token, '\n');
		}
		else
		{
			current_token = combine_tokens(current_token, s[lexer.i]);
			lexer.i++;
		}
	}
	write(1, "end of lexer\n", 13);
	printf("tokens: %s\n", current_token);
	int b = -1;
	char **new = ft_split(current_token, '\n');
	printf("each token:\n");
//	while(new[++b])
//	{
//		printf("token number %d: %s\n", b, new[b]);
//	}
	b = -1;
	while(new[++b])
	{
		printf("token number %d: %s\n", b, new[b]);
	}
	printf("\n");
	return (0);
}

int main()
{
	char *s = user_input();
	return (lexer(s));
}
