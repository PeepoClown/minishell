#include <minishell.h>

char	**extend_arr(char **mod_array, char *line)
{
	char	**copy;
	int		arr_size = 0;
	int	i = -1;

	if (mod_array != NULL)
		while (mod_array[arr_size] != NULL) 
			arr_size++;
	copy = (char**)malloc(sizeof(char*) * (arr_size + 2));
	i = -1;
	while (++i < arr_size)
	{
		copy[i] = ft_strdup(mod_array[i]);
	}
	copy[i++] = ft_strdup(line);
	copy[i] = NULL;
	free(line);
	line = NULL;
	ft_remove_char_matrix(mod_array);
	return (copy);
}

void	fill_struct_redirects(t_cmd **tmp, char **input, t_env *env, int *i)
{
	if (!(ft_strcmp(input[*i], ">")))
	{
		if (input[*i + 1] != NULL)
		{
			(*tmp)->redir_out = extend_arr((*tmp)->redir_out, parse_tokens(input[*i + 1], env));
			(*tmp)->last_out_redir_type = TRUNC;
			if ((*tmp)->last_out_redir)
				free((*tmp)->last_out_redir);
			(*tmp)->last_out_redir = parse_tokens(input[*i + 1], env);
			(*i)++;
		}
		// else
			// error bash: syntax error near unexpected token `newline'
	}
	else if (!(ft_strcmp(input[*i], ">>")))
	{
		if (input[*i + 1] != NULL)
		{
			(*tmp)->redir_append_out = extend_arr((*tmp)->redir_append_out, parse_tokens(input[*i + 1], env));
			(*tmp)->last_out_redir_type = APPEND;
			if ((*tmp)->last_out_redir)
				free((*tmp)->last_out_redir);
			(*tmp)->last_out_redir = parse_tokens(input[*i + 1], env);
			(*i)++;
		}
		// else
			// error
	}
	else if (!(ft_strcmp(input[*i], "<")))
	{
		if (input[*i + 1] != NULL)
		{
			(*tmp)->redir_in = extend_arr((*tmp)->redir_in, parse_tokens(input[*i + 1], env));
			(*i)++;
		}
		// else
			// error
	}
}

void	fill_structure(t_cmd **tmp, char **input, t_env *env, int *j)
{
	if (!(*tmp)->name && ft_strcmp(input[*j], ">>") &&
		ft_strcmp(input[*j], ">") && ft_strcmp(input[*j], "<"))
		(*tmp)->name = parse_tokens(input[*j], env);
	else if (!(ft_strcmp(input[*j], ">")) || !(ft_strcmp(input[*j], ">>")) ||
			!(ft_strcmp(input[*j], "<")))
		fill_struct_redirects(tmp, input, env, j);
	else
		(*tmp)->args = extend_arr((*tmp)->args, parse_tokens(input[*j], env));
}

void	parse_input(t_cmd **cmd, char **input, int *i, t_env *env)
{
	t_cmd *tmp = ft_lst_new();
	*cmd = tmp;
	while(input[*i])
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
