/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:33:10 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:33:11 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strtrim(char *s1, char const *set)
{
	char	*trimmed;
	char	*p;
	int		i;

	p = s1;
	if (!s1 || (!s1 && !set))
		return (NULL);
	while (*p && ft_strchr(set, *p))
		p++;
	i = ft_strlen(p);
	while (i > 0 && ft_strchr(set, p[i - 1]))
		i--;
	if (i == 0)
		return (ft_strdup(""));
	trimmed = ft_substr(p, 0, i);
	return (trimmed);
}
