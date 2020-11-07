/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:03:32 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:03:33 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*copy_env(t_env *env)
{
	t_env	*copy;
	t_env	*curr;

	if (!env)
		return (NULL);
	if (!(curr = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	copy = curr;
	while (env != NULL)
	{
		curr->key = ft_strdup(env->key);
		curr->value = ft_strdup(env->value);
		curr->is_hidden = env->is_hidden;
		if (env->next != NULL)
		{
			if (!(curr->next = (t_env*)malloc(sizeof(t_env))))
				return (NULL);
			curr = curr->next;
		}
		env = env->next;
	}
	curr->next = NULL;
	return (copy);
}
