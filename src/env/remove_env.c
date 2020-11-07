/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:04:01 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 18:04:02 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_env(t_env **env)
{
	t_env	*list;
	t_env	*tmp;

	list = *env;
	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		del_env_item(tmp);
	}
	*env = NULL;
}
