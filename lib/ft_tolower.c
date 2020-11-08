/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:12:57 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/08 18:12:58 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

static int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

char		*str_to_lower(char *s)
{
	char	*t;
	int		i;

	if (!s)
		return (s);
	i = ft_strlen(s);
	if (!(t = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s[++i])
		t[i] = (char)ft_tolower((int)s[i]);
	t[i] = '\0';
	free(s);
	s = NULL;
	return (t);
}
