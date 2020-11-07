/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:03:51 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:03:52 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_env_key(t_env *env, const char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_path_env_var(t_env *env, const char *path)
{
	char	*tmp;

	tmp = ft_strjoin("_=", path);
	add_to_env(env, tmp);
	free(tmp);
	set_env_hidden(env, "_", ENV_VIS);
}
