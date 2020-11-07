/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:25:51 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:25:53 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	escape_char(char c)
{
	int		i;
	char	*t;
	char	*escape;

	escape = "\n\t\\\'";
	i = 0;
	t = "nt\\\'";
	while (t[i] && t[i] != c)
		i++;
	return (escape[i]);
}

int		env_single_quote(char *s, char **token)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != '\'')
	{
		if (s[i] == '\\' && ft_strchr("nt\\\'", s[i + 1]))
		{
			i++;
			*token = add_char(*token, escape_char(s[i]));
		}
		else
			*token = add_char(*token, s[i]);
		i++;
	}
	return (i + 1);
}

int		env_status(char *s, int i, char **token, char *tmp)
{
	char	*tmp_num;

	if (s[i] == '\'')
		return (env_single_quote(&s[i], token));
	tmp_num = ft_itoa(g_status);
	*token = ft_strjoin(*token, tmp_num);
	free(tmp);
	free(tmp_num);
	return (i + 1);
}

int		replace_env(char *s, t_env *env, char **token, int flag)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 1;
	tmp = *token;
	if (!s[i])
		*token = add_char(*token, s[0]);
	else if (ft_isdigit(s[i]))
		return (i + 1);
	else if ((s[i] == '\'' && !flag) || s[i] == '?')
		return (env_status(s, i, token, tmp));
	else
		while (!ft_isdigit(s[i]) && !ft_strchr("\"\'\\ $=", s[i]))
			i++;
	if (i == 1)
		return (i);
	path = ft_substr(s, 1, i - 1);
	*token = ft_strjoin(*token, get_env_value(env, path));
	free(tmp);
	free(path);
	path = NULL;
	return (i);
}
