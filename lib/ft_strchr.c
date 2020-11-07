/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:32:44 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:32:45 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;

	i = 0;
	if (!s)
		return (NULL);
	a = NULL;
	while (s[i])
	{
		if (s[i] == c)
			a = ((char *)s + i);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		a = ((char *)s + i);
	return (a);
}
