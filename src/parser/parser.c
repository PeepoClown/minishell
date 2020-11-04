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
		copy[i] = ft_strdup(mod_array[i]);
	copy[i++] = ft_strdup(line);
	copy[i] = NULL;
	// free mod_array
	return (copy);
}

void	fill_struct_redirects(t_cmd **tmp, char **input, t_env *env, int i)
{
	if (!(ft_strcmp(input[i], ">")))
	{
		(*tmp)->last_out_redir_type = TRUNC;
		(*tmp)->last_out_redir = ft_strdup(parse_tokens(input[i++], env));
		(*tmp)->redir_out = extend_arr((*tmp)->redir_out, parse_tokens(input[i], env));
	}
	else if (!(ft_strcmp(input[i], ">>")))
	{
		(*tmp)->last_out_redir_type = APPEND;
		(*tmp)->last_out_redir = ft_strdup(parse_tokens(input[i++], env));
		(*tmp)->redir_append_out = extend_arr((*tmp)->redir_append_out, parse_tokens(input[i], env));
	}
	else if (!(ft_strcmp(input[i], "<")))
	{
		(*tmp)->redir_in = extend_arr((*tmp)->redir_in, parse_tokens(input[++i], env));
	}
}

void	fill_structure(t_cmd **tmp, char **input, t_env *env, int *j)
{
	int i;

	i = *j;
	if (!(*tmp)->name && ft_strcmp(input[i], ">>") &&
		ft_strcmp(input[i], ">") && ft_strcmp(input[i], "<"))
		(*tmp)->name = parse_tokens(input[i], env);
	else if (!(ft_strcmp(input[i], ">")) || !(ft_strcmp(input[i], ">>")) ||
			!(ft_strcmp(input[i], "<")))
		fill_struct_redirects(tmp, input, env, i);
	else
		(*tmp)->args = extend_arr((*tmp)->args, parse_tokens(input[i], env));
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
