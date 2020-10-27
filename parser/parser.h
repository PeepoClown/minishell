/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:40:09 by qcraghas          #+#    #+#             */
/*   Updated: 2020/10/25 17:49:34 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../include/minishell.h"
# include "../lib/lib.h"

void	parse_input(t_cmd **cmd, char *input); //check this function
int		get_arguments(t_cmd *cmd, char *s);
int		get_command(t_cmd *cmd, char *s);

/*
** processing quotes
*/

int		double_quotes(char *s, char **token);
int		single_quotes(char *s, char **token);

/*
** utilities and auxularies
*/

char	*add_char(char *s, char c);
t_cmd	*ft_lst_new();
void	ft_lst_add_back(t_cmd **cmd, t_cmd *new);
int		array_size(char **array);
int		free_array(char **array);
char	**add_string_to_array(t_cmd *cmd, char *arg);

#endif