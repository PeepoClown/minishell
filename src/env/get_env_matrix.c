/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:03:42 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/08 14:02:25 by wupdegra         ###   ########.fr       */
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

static	int		count_visible(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->is_hidden == VISIBLE || tmp->is_hidden == ENV_VIS)
			count++;
		tmp = tmp->next;
	}
	return (count);
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
	if (!(matrix = (char**)malloc(sizeof(char*) * (count_visible(env) + 1))))
		return (NULL);
	count = 0;
	tmp_env = env;
	while (tmp_env != NULL)
	{
		if (tmp_env->is_hidden == VISIBLE || tmp_env->is_hidden == ENV_VIS)
			matrix[count++] = concat_env(tmp_env);
		tmp_env = tmp_env->next;
	}
	matrix[count] = NULL;
	return (matrix);
}
