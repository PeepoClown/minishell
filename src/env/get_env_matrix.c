/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:03:42 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:03:43 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char	*concat_env(t_env *env)
{
	char	*tmp;
	char	*res;

	res = ft_strdup(env->key);
	tmp = res;
	res = ft_strjoin(res, "=");
	free(tmp);
	tmp = res;
	res = ft_strjoin(res, env->value);
	free(tmp);
	return (res);
}

char			**get_env_matrix(t_env *env)
{
	char	**matrix;
	t_env	*tmp_env;
	int		count;

	count = 0;
	tmp_env = env;
	while (tmp_env != NULL)
	{
		count++;
		tmp_env = tmp_env->next;
	}
	if (!(matrix = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	count = 0;
	tmp_env = env;
	while (tmp_env != NULL)
	{
		matrix[count] = concat_env(tmp_env);
		tmp_env = tmp_env->next;
		count++;
	}
	matrix[count] = NULL;
	return (matrix);
}
