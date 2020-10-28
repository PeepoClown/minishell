/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:48:05 by qcraghas          #+#    #+#             */
/*   Updated: 2020/10/25 17:48:29 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_char(char *s, char c)
{
	int i;
	char *new;

//	if (!s)
//	{
//		s = (char *) malloc(sizeof(char));
//		*s = '\0';
//	}
	i = ft_strlen(s);
	if (!(new = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = -1;
	while(s[++i])
		new[i] = s[i];
	new[i++] = c;
	new[i] = '\0';
	free(s);
	s = NULL;
	return(new); 
}

t_cmd	*ft_lst_new()
{
	t_cmd *tmp;

	if(!(tmp = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	tmp->name = NULL;
	tmp->args = (char **)malloc(sizeof(char *));
	tmp->args[0] = NULL;
	tmp->fd_in = 0;
	tmp->fd_out = 0;
	tmp->fd_append_out = 0;
	tmp->pipe = 0;
	tmp->next = NULL;
	return (tmp);
}

void	ft_lst_add_back(t_cmd **cmd, t_cmd *new) //lstnew
{
	t_cmd *a;

	a = *cmd;
	if (a)
	{
		while (a->next)
			a = a->next;
		a->next = new;
	}
	else
		*cmd = new;
}

