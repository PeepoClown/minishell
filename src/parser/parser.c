/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:46:24 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 16:46:26 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	out_redirects(t_cmd **tmp, char **input, t_env *env, int *i)
{
	if (!ft_strcmp(input[*i], ">"))
	{
		(*tmp)->redir_out = extend_arr((*tmp)->redir_out,
						parse_tokens(input[*i + 1], env));
		(*tmp)->last_out_redir_type = TRUNC;
		if ((*tmp)->last_out_redir)
			free((*tmp)->last_out_redir);
		(*tmp)->last_out_redir = parse_tokens(input[*i + 1], env);
		(*i)++;
	}
	else if (!(ft_strcmp(input[*i], ">>")))
	{
		(*tmp)->redir_append_out = extend_arr((*tmp)->redir_append_out,
						parse_tokens(input[*i + 1], env));
		(*tmp)->last_out_redir_type = APPEND;
		if ((*tmp)->last_out_redir)
			free((*tmp)->last_out_redir);
		(*tmp)->last_out_redir = parse_tokens(input[*i + 1], env);
		(*i)++;
	}
}

int			fill_struct_redirects(t_cmd **tmp, char **input, t_env *env, int *i)
{
	if (!ft_strcmp(input[*i], ">") || !ft_strcmp(input[*i], ">>"))
		out_redirects(tmp, input, env, i);
	else if (!(ft_strcmp(input[*i], "<")))
	{
		if (input[*i + 1] != NULL)
		{
			(*tmp)->redir_in = extend_arr((*tmp)->redir_in,
							parse_tokens(input[*i + 1], env));
			(*i)++;
		}
	}
	return (1);
}

void		split_env(t_cmd **tmp, char *name)
{
	char	**split_env;
	int		i;
	int		size;

	i = 0;
	split_env = ft_split(name, ' ');
	if ((size = array_size(split_env)) < 2)
	{
		free((*tmp)->name);
		(*tmp)->name = name;
		ft_remove_char_matrix(split_env);
		return ;
	}
	free(name);
	free((*tmp)->name);
	(*tmp)->name = ft_strdup(split_env[i]);
	(*tmp)->name = str_to_lower((*tmp)->name);
	free(split_env[i++]);
	while (i < size)
	{
		(*tmp)->args = extend_arr((*tmp)->args, split_env[i]);
		i++;
	}
	free(split_env);
}

void		fill_structure(t_cmd **tmp, char **input, t_env *env, int *j)
{
	char	*name;
	char	*s;

	if (!(*tmp)->name && ft_strcmp(input[*j], ">>") &&
		ft_strcmp(input[*j], ">") && ft_strcmp(input[*j], "<"))
	{
		name = parse_tokens(input[*j], env);
		if (*input[*j] == '$')
			split_env(tmp, name);
		else
			(*tmp)->name = str_to_lower(name);
	}
	else if (!(ft_strcmp(input[*j], ">")) || !(ft_strcmp(input[*j], ">>")) ||
			!(ft_strcmp(input[*j], "<")))
		fill_struct_redirects(tmp, input, env, j);
	else
	{
		s = parse_tokens(input[*j], env);
		if (s != NULL)
			(*tmp)->args = extend_arr((*tmp)->args, s);
	}
}

void		parse_input(t_cmd **cmd, char **input, int *i, t_env *env)
{
	t_cmd *tmp;

	tmp = ft_lst_new();
	*cmd = tmp;
	while (input[*i])
	{
		if (!(ft_strcmp(input[*i], ";")))
		{
			(*i)++;
			break ;
		}
		if (!(ft_strcmp(input[*i], "|")))
		{
			tmp->pipe_status = true;
			tmp->next = ft_lst_new();
			tmp = tmp->next;
			(*i)++;
			continue ;
		}
		fill_structure(&tmp, input, env, i);
		(*i)++;
	}
}
