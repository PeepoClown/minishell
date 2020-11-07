/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:33:05 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:33:06 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

size_t	ft_strlen(const char *str)
{
	size_t count;

	count = 0;
	if (!str)
		return (0);
	while (*(str + count))
		count++;
	return (count);
}
