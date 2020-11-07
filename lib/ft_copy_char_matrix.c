/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_char_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:30:47 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:30:52 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

char	**ft_copy_char_matrix(char **matrix, int row)
{
	int		i;
	char	**res;

	if (!(res = (char**)malloc(sizeof(char*) * (row + 1))))
		return (NULL);
	i = 0;
	while (i < row)
	{
		res[i] = ft_strdup(matrix[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
