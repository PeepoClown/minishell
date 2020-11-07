/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:32:20 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:32:21 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	itoa_count(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static char	*itoa_string(int n, int b)
{
	char	*itoa;
	int		i;

	i = 0;
	itoa = malloc(sizeof(char) * (b + 1));
	if (itoa == NULL)
		return (NULL);
	itoa[b] = '\0';
	if (n < 0)
	{
		itoa[i] = '-';
		n *= -1;
		i++;
	}
	while (n > 9 && --b > 0)
	{
		itoa[b] = n % 10 + '0';
		n = n / 10;
	}
	if (n >= 0)
		itoa[i] = n + '0';
	return (itoa);
}

char		*ft_itoa(int n)
{
	char	*itoa;
	int		b;

	if (n == -2147483648)
		return (ft_substr("-2147483648", 0, 11));
	b = itoa_count(n);
	itoa = itoa_string(n, b);
	return (itoa);
}
