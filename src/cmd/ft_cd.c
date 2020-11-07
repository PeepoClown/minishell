/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:00:46 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 22:57:54 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char	*replace_path(char *path, t_env *env)
{
	char	*res;
	char	*tmp;

	if (path[0] != '~' && path[0] != '-')
		return (NULL);
	res = NULL;
	if (path[0] == '~')
	{
		tmp = ft_substr(path, 1, ft_strlen(path));
		res = ft_strjoin(g_home, tmp);
		free(tmp);
	}
	else if (!ft_strcmp(path, "-"))
	{
		if (!get_env_value(env, "OLDPWD"))
			return (NULL);
		res = ft_strdup(get_env_value(env, "OLDPWD"));
	}
	return (res);
}

static	void	set_pwd(t_env *env, const char *type)
{
	char	*cwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	path = ft_strjoin(type, cwd);
	add_to_env(env, path);
	free(cwd);
	free(path);
}

static	int		oldpwd_handler(t_cmd *cmd, t_env *env, char *path)
{
	struct stat stat_buff;

	if (!ft_strcmp(path, "-"))
	{
		ft_error(cmd->name, NULL, "OLDPWD not set");
		return (0);
	}
	if (!ft_strcmp(*(cmd->args), "-"))
	{
		ft_putstr_fd(path, cmd->fd_out);
		ft_putendl_fd(cmd->fd_out);
	}
	stat(path, &stat_buff);
	if (S_ISDIR(stat_buff.st_mode) == true)
		set_pwd(env, "OLDPWD=");
	return (1);
}

static	void	removing_cd(char *dest_path, char *path, t_env *env)
{
	set_pwd(env, "PWD=");
	if (path != NULL)
		free(path);
	if (!ft_strcmp(dest_path, "./"))
		free(dest_path);
}

int				ft_cd(t_cmd *cmd, t_env *env)
{
	char	*dest_path;
	char	*path_with_home;

	if (*(cmd->args) == NULL)
	{
		free(cmd->args);
		cmd->args = (char**)malloc(sizeof(char*) * 2);
		*(cmd->args) = ft_strdup("~");
		*(cmd->args + 1) = NULL;
	}
	path_with_home = replace_path(*(cmd->args), env);
	dest_path = (path_with_home != NULL) ? path_with_home : *(cmd->args);
	if (*dest_path == '\0')
		dest_path = ft_strdup("./");
	if (!oldpwd_handler(cmd, env, dest_path))
		return (1);
	if ((chdir(dest_path) < 0))
	{
		if (path_with_home != NULL)
			free(path_with_home);
		ft_error(cmd->name, dest_path, strerror(errno));
		return (1);
	}
	removing_cd(dest_path, path_with_home, env);
	return (0);
}
