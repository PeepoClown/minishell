/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:32:37 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 22:49:40 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

void	ft_remove_char_matrix(char **matrix)
{
	int		i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
