/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:02:10 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 21:20:43 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void			init_prompt_vars(t_env *env)
{
	g_user = ft_strdup(get_env_value(env, "USER"));
	g_home = ft_strdup(get_env_value(env, "HOME"));
	g_home_const = ft_strdup(get_env_value(env, "HOME"));
	g_status = 0;
	g_is_copy_rm = false;
	g_input_start = false;
}

void			remove_prompt_vars(char *user, char *home, char *home_const)
{
	free(user);
	free(home);
	free(home_const);
}

static	void	set_slash_zero(int *i, int *j, char *path_with_home)
{
	path_with_home[0] = '~';
	*i = ft_strlen(g_home);
	*j = 1;
}

static	char	*init_home_path(void)
{
	char	*path;
	char	*path_with_home;
	int		i;
	int		j;

	path = getcwd(NULL, 0);
	path_with_home = ft_substr(path, 0, ft_strlen(g_home));
	if (ft_strcmp(path_with_home, g_home) == 0)
	{
		free(path_with_home);
		path_with_home = (char*)malloc(sizeof(char) * (ft_strlen(path) -
			ft_strlen(g_home) + 2));
		set_slash_zero(&i, &j, path_with_home);
		while (i < (int)ft_strlen(path))
			path_with_home[j++] = path[i++];
		path_with_home[j] = '\0';
		free(path);
		return (path_with_home);
	}
	else
	{
		free(path_with_home);
		return (path);
	}
}

void			display_prompt(void)
{
	char	*path;

	path = (g_home != NULL) ? init_home_path() : NULL;
	ft_putstr_fd("\e[1;34m[ ", 1);
	if (g_user != NULL)
	{
		ft_putstr_fd("\e[1;31m", 1);
		ft_putstr_fd(g_user, 1);
	}
	if (g_home != NULL)
	{
		ft_putstr_fd("\e[1;31m:", 1);
		ft_putstr_fd(path, 1);
	}
	ft_putstr_fd("\e[1;34m ]\n\e[0m", 1);
	ft_putstr_fd("(current status : \e[4;33m", 1);
	ft_putnbr_fd(g_status, 1);
	ft_putstr_fd("\e[0m ) $> ", 1);
	if (path != NULL)
		free(path);
}
