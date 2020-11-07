/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:33:14 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:33:15 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

char	*ft_substr(const char *s, int start, size_t len)
{
	char	*str;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	if ((int)ft_strlen((char*)s) <= start)
		return (ft_strdup(""));
	size = ft_strlen((char*)s + start);
	if ((int)len > size)
		len = size;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < (int)len)
	{
		*(str + i) = *(s + start + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
