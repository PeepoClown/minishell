/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:56:51 by qcraghas          #+#    #+#             */
/*   Updated: 2020/10/25 17:56:52 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		array_size(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i])
		i++;
	return (i);
}

char	*add_char(char *s, char c)
{
	int		i;
	char	*new;

	i = ft_strlen(s);
	if (!(new = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = -1;
	while (s[++i])
		new[i] = s[i];
	new[i++] = c;
	new[i] = '\0';
	free(s);
	s = NULL;
	return (new);
}

char	*combine_tokens(char *token, char c)
{
	char	*s;

	if (!token)
		token = ft_strdup("");
	s = add_char(token, c);
	return (s);
}
