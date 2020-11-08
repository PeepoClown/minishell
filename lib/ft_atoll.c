/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:48:34 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/08 17:15:31 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

unsigned long long	ft_atoll(const char *str)
{
	int					sign;
	unsigned long long	result;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str && *str >= 48 && *str <= 57)
		result = result * 10 + (*str++ - 48);
	return (result * sign);
}
