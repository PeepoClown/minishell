/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:46:05 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/06 22:17:09 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	escape_char(char c)
{
	int i;
	//char *s;
	char *t;
	char escape[10] = { '\a', '\n', '\e', '\f', '\n', '\r', '\t', '\v', '\\', '\''};
	i = 0;
	t = "anefnrtv\\\'";
	while (t[i] && t[i] != c)
		i++;
	return (escape[i]);
}

int	env_single_quote(char *s, char **token)
{
	int	i;

	i = 1;
	while(s[i] && s[i] != '\'')
	{
		if (s[i] == '\\' && ft_strchr("abefnrtv\\\'", s[i + 1]))
		{
			i++;
			*token = add_char(*token, escape_char(s[i]));
			if (s[i] == '\'')
				i++;
		}
		else
			*token = add_char(*token, s[i]);
		i++;
	}
	return (i + 1);
}

int replace_env(char *s, t_env *env, char **token)
{
	int i;
	char *path;
	char *tmp;
	char *tmp_num;

	i = 1;
	tmp = *token;
	if (!s[i])
		*token = add_char(*token, s[0]);
	else if (ft_isdigit(s[i]))
		return (i + 1);
	else if (s[i] == '\'')
		return (env_single_quote(&s[i], token));
	else if (s[i] == '?')
	{
		tmp_num = ft_itoa(g_status);
		*token = ft_strjoin(*token, tmp_num);
		free(tmp);
		free(tmp_num);
		return (i + 1);
	}
	else
		while(!ft_isdigit(s[i]) && !ft_strchr("\"\'\\ $=", s[i]))
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

int		double_quotes(char *s, char **token, t_env *env)
{
	int i = 1;

	while(s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			break ;
		}
		if (s[i] == '$')
		{
			i += replace_env(&s[i], env, token);
			continue ;
		}
		if (s[i] == '\\')
		{
			if (s[i + 1] != '\\' && s[i + 1] != '\"' && s[i + 1] != '$')
				*token = add_char(*token, s[i]);
			i++;
		}
		if (!s[i])
			break ;
		*token = add_char(*token, s[i]);
		i++;
	}
	return (i);
}

int		single_quotes(char *s, char **token)
{
	int i = 0;
	if (*s++ == '\'')
		i++;
	while(*s)
	{
		if (*s == '\'')
		{
			i++;
			break ;
		}
		if (!*s)
			break ;
		*token = add_char(*token, *s);
		i++;
		s++;
	}
	return (i);
}

