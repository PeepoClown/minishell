/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:04:04 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:04:05 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	swap_env_items(t_env *item1, t_env *item2)
{
	char	*key;
	char	*value;
	int		is_hidden;

	key = item1->key;
	value = item1->value;
	item1->key = item2->key;
	item1->value = item2->value;
	item2->key = key;
	item2->value = value;
	is_hidden = item1->is_hidden;
	item1->is_hidden = item2->is_hidden;
	item2->is_hidden = is_hidden;
}

void			sort_env(t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	if ((env == NULL) || (*env == NULL))
		return ;
	tmp = *env;
	while (tmp != NULL)
	{
		curr = *env;
		while (curr->next != NULL)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
				swap_env_items(curr, curr->next);
			curr = curr->next;
		}
		tmp = tmp->next;
	}
}
