/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:48:05 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 22:43:54 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*ft_lst_new(void)
{
	t_cmd *tmp;

	if (!(tmp = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	tmp->name = NULL;
	tmp->args = (char**)malloc(sizeof(char*));
	tmp->args[0] = NULL;
	tmp->fd_in = 0;
	tmp->fd_out = 0;
	tmp->redir_out = (char**)malloc(sizeof(char*));
	tmp->redir_out[0] = NULL;
	tmp->redir_append_out = (char**)malloc(sizeof(char*));
	tmp->redir_append_out[0] = NULL;
	tmp->last_out_redir = NULL;
	tmp->last_out_redir_type = NONE;
	tmp->redir_in = (char**)malloc(sizeof(char*));
	tmp->redir_in[0] = NULL;
	tmp->pipe_status = false;
	tmp->next = NULL;
	tmp->builtin = NULL;
	return (tmp);
}

void	ft_remove_cmd(t_cmd *cmd)
{
	t_cmd	*list;
	t_cmd	*tmp;

	list = cmd;
	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		if (tmp->name)
			free(tmp->name);
		ft_remove_char_matrix(tmp->args);
		ft_remove_char_matrix(tmp->redir_out);
		ft_remove_char_matrix(tmp->redir_append_out);
		ft_remove_char_matrix(tmp->redir_in);
		if (tmp->last_out_redir)
			free(tmp->last_out_redir);
		if (tmp->builtin)
		{
			if (tmp->builtin->cmd)
				free(tmp->builtin->cmd);
			free(tmp->builtin);
		}
		free(tmp);
	}
}
