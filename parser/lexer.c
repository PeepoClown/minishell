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

int		check_quote_pair(char *s, char quote, int *error)
{
	int i = 1;

	*error = 1;
	if (!s[i])
		error = 0;
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

int		lexer(char *s)
{
	int i = 0;
	int error = 0;
	char match_quote;
	i += skip_spaces(s);
	if (s[i] == ';' || s[i] == '|')
	{
		write(1, "bash: syntax error near unexpected token `", 42);
		write(1, &s[i], 1);
		write(1, "'\n", 2);
		return (1);
	}
	while(s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			match_quote = s[i];
//			printf("match quote: |%c|", s[i]);
			write(1, &s[i], 1);
			write(1, "\n", 1);
			i += check_quote_pair(&s[i], s[i], &error);
			write(1, &s[i], 1);
			write(1, "\n", 1);
//			printf("offset in quotes: |%d|", i);
		}
		else if (s[i] == ';')
		{
			i += skip_spaces(&s[i]) + 1;
			if (s[i] == ';')
			{
				write(1, "bash: syntax error near unexpected token `", 42);
				write(1, &s[i], 1);
				write(1, "'\n", 2);
				return (1);
			}
		}
		else
			i++;
		if (error)
		{
			write(1, "bash: unexpected EOF while looking for matching ", 48); //not matching quotes
			write(1, &match_quote, 1);
			write(1, "\n", 1);
			return (1);
		}
	}
	write(1, "end of lexer\n", 13);
	return (0);
}

int main()
{
	char *s = user_input();
	return (lexer(s));
}
