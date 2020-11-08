/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_hidden_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:02:22 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/08 15:36:20 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	bool	validate_hidden_env_name(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name != '=')
	{
		if (!ft_isalpha(*name) && *name != '_' && !ft_isdigit(*name))
			return (false);
		name++;
	}
	return (true);
}

static	void	decrease_cmd_args(t_cmd *cmd)
{
	char	**matrix;
	int		i;

	i = 1;
	if (!(matrix = (char**)malloc(sizeof(char*) * array_size(cmd->args))))
		return ;
	while (cmd->args[i] != NULL)
	{
		matrix[i - 1] = ft_strdup(cmd->args[i]);
		i++;
	}
	matrix[i - 1] = NULL;
	ft_remove_char_matrix(cmd->args);
	cmd->args = matrix;
}

static	void	add_to_env_hidden_null(t_env *env, char *line)
{
	char	*tmp;
	t_env	*tmp_env;

	tmp = ft_substr(line, 0, ft_find_first_of(line, '='));
	add_to_env(env, tmp);
	tmp_env = env;
	while (tmp_env != NULL)
	{
		if (!ft_strcmp(tmp, tmp_env->key))
			break ;
		tmp_env = tmp_env->next;
	}
	if (tmp_env != NULL)
		set_env_hidden(env, tmp_env->key, EXPORT_VIS);
	free(tmp);
}

void			validate_hidden_env(t_env *env, t_cmd *cmd)
{
	char	*key;

	while (ft_find_first_of(cmd->name, '=') != -1)
	{
		if (validate_hidden_env_name(cmd->name) == false)
			break ;
		key = ft_substr(cmd->name, 0, ft_find_first_of(cmd->name, '='));
		if (check_env_key(env, key) == true)
			change_env_value(env, cmd->name);
		else
		{
			if (cmd->name[ft_find_first_of(cmd->name, '=') + 1] == '\0')
				add_to_env_hidden_null(env, cmd->name);
			else
				add_to_env(env, cmd->name);
			set_env_hidden(env, key, HIDDEN);
		}
		free(key);
		free(cmd->name);
		cmd->name = ft_strdup(cmd->args[0]);
		if (cmd->name == NULL)
			break ;
		decrease_cmd_args(cmd);
	}
}
