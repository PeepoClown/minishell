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

char	**extend_arr(char **mod_array, char *line)
{
	char	**copy;
	int		arr_size;
	int		i;

	arr_size = 0;
	i = -1;
	if (mod_array != NULL)
		while (mod_array[arr_size] != NULL)
			arr_size++;
	copy = (char**)malloc(sizeof(char*) * (arr_size + 2));
	i = -1;
	while (++i < arr_size)
	{
		copy[i] = ft_strdup(mod_array[i]);
	}
	copy[i++] = ft_strdup(line);
	copy[i] = NULL;
	free(line);
	line = NULL;
	ft_remove_char_matrix(mod_array);
	return (copy);
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
