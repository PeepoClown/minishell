/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:56:51 by qcraghas          #+#    #+#             */
/*   Updated: 2020/10/25 17:56:52 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		array_size(char **array)
{
	int	i;

	i = 0;
	printf("arr size %d\n", i);
//	printf("arr elem %s\n", array[i]);
//	if (!array)
//		return (0);
	while (array[i])
		i++;
	printf("--->arr size %d\n", i);
	return (i);
}

int		free_array(char **array)
{
	int	i;

	i = array_size(array);
	while (i >= 0)
	{
		free(array[i]);
		array[i] = NULL;
		i--;
	}
	free(array);
	array = NULL;
	return (i);
}

char *combine_tokens(char *token, char c)
{
	char	*s;

	if (!token)
		token = ft_strdup("");
	s = add_char(token, c);
	return (s);
}

char	**add_token_to_array(t_lexer *lexer, char *arg, int i)
{
	char	**new;

	printf("arr size %d\n", i);
	if (!(new = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (lexer->tokens[++i])
		new[i] = lexer->tokens[i];
	new[i++] = ft_strdup(arg);
	new[i] = NULL;
//	free_array(cmd->args);
	return (new);
}
char	**add_string_to_array(t_cmd *cmd, char *arg)
{
	char	**new;
	int		i;

	i = array_size(cmd->args);
	printf("arr size %d\n", i);
	if (!(new = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (cmd->args[++i])
		new[i] = cmd->args[i];
	new[i++] = ft_strdup(arg);
	new[i] = NULL;
//	free_array(cmd->args);
	return (new);
}