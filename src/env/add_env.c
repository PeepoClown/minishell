/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:03:25 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/08 14:45:05 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void			add_env(t_env **env, const char *line)
{
	t_env	*item;

	if (!env)
		return ;
	if ((*env) == NULL)
		*env = create_env_item(line);
	else
	{
		item = *env;
		while (item->next != NULL)
			item = item->next;
		item->next = create_env_item(line);
	}
}

static	void	modify_user_prompt(const char *line)
{
	char	*user;

	if (ft_find_first_of(line, '=') == -1)
		return ;
	user = ft_substr(line, ft_find_first_of(line, '=') + 1, ft_strlen(line));
	if (g_user != NULL)
		free(g_user);
	g_user = ft_strdup(user);
	free(user);
}

static	void	set_home_dir(const char *line)
{
	char	*home;

	if (ft_find_first_of(line, '=') == -1)
		return ;
	if (line[ft_find_first_of(line, '=') + 1] == '\0')
		home = ft_strdup(g_home_const);
	else
		home = ft_substr(line, ft_find_first_of(line, '=') + 1,
			ft_strlen(line));
	if (g_home != NULL)
		free(g_home);
	g_home = ft_strdup(home);
	free(home);
}

void			add_to_env(t_env *env, const char *line)
{
	char	*key;

	key = (ft_find_first_of(line, '=') == -1)
		? ft_strdup(line)
		: ft_substr(line, 0, ft_find_first_of(line, '='));
	if (!ft_strcmp(key, "USER"))
		modify_user_prompt(line);
	if (!ft_strcmp(key, "HOME"))
		set_home_dir(line);
	if (check_env_key(env, key) == true)
	{
		if (ft_find_first_of(line, '=') >= 0)
			change_env_value(env, line);
		if (get_env_value(env, key) != NULL)
			set_env_hidden(env, key, VISIBLE);
		else
			set_env_hidden(env, key, EXPORT_VIS);
		free(key);
		return ;
	}
	add_env(&env, line);
	if (ft_find_first_of(line, '=') == -1)
		set_env_hidden(env, key, EXPORT_VIS);
	free(key);
}
