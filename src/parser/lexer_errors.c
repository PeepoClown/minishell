/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:43:53 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 16:43:56 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	quote_pair(char *s, char quote, int *error)
{
	int i;

	i = 1;
	*error = 1;
	if (!s[i])
		*error = 1;
	if (s[i] == quote)
	{
		*error = 0;
		return (i + 1);
	}
	while (s[i] != quote && s[i] != '\0')
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

int	unexpected_token(char unexpected)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, &unexpected, 1);
	write(2, "'\n", 2);
	g_status = 258;
	return (0);
}

int	unexpected_redirects(void)
{
	write(2, "bash: syntax error near unexpected token `newline'\n", 51);
	g_status = 258;
	return (0);
}

int	unexpected_eof(char match_quote)
{
	write(2, "bash: unexpected EOF while looking for matching `", 49);
	write(2, &match_quote, 1);
	write(2, "\"\n", 2);
	g_status = 258;
	return (0);
}
