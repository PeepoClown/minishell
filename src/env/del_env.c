/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:03:39 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:03:40 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void			del_env_item(t_env *env)
{
	if (!ft_strcmp(env->key, "USER") && !g_is_copy_rm)
	{
		if (g_user != NULL)
			free(g_user);
		g_user = ft_strdup("defaultUser");
	}
	if (!ft_strcmp(env->key, "HOME") && !g_is_copy_rm)
	{
		if (g_home != NULL)
			free(g_home);
		g_home = ft_strdup(g_home_const);
	}
	free(env->key);
	if (env->value != NULL)
		free(env->value);
	free(env);
}

void			del_env(t_env **env, const char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !check_env_key(*env, key))
		return ;
	if (ft_strcmp((*env)->key, key) == 0)
	{
		tmp = (*env)->next;
		del_env_item(*env);
		*env = tmp;
	}
	else
	{
		tmp = *env;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->key, key) == 0)
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = tmp->next;
		del_env_item(tmp);
	}
}
