/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:01:56 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/08 13:54:36 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char	*add_to_str(char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	res = (char*)malloc((ft_strlen(str) + 2) * sizeof(char));
	while (i < (int)ft_strlen(str))
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	if (str)
		free(str);
	return (res);
}

static	void	input_loop(char ch, int read_res, char **input)
{
	if (!g_input_start)
	{
		free(*input);
		*input = ft_strdup("");
		g_input_start = true;
	}
	if (**input == '\0' && read_res == 0)
	{
		ft_putstr_fd("exit\n", 1);
		free(*input);
		exit(g_status);
	}
	else if (read_res == 0)
		ft_putstr_fd("  \b\b", 1);
	else
		*input = add_to_str(*input, ch);
}

char			*user_input(void)
{
	char	*input;
	char	buff[1];
	int		read_res;

	g_input_start = true;
	input = ft_strdup("");
	while ((read_res = read(0, buff, 1)) >= 0)
	{
		if (buff[0] == '\n')
			break ;
		input_loop(buff[0], read_res, &input);
	}
	if (read_res == -1)
		exit (g_status);
	g_input_start = false;
	return (input);
}
