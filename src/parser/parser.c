#include <minishell.h>

void	print_struct(t_cmd *cmd)
{
	while(cmd)
	{
		printf("cmd name: %s\n", cmd->name);
		int i = 0;
		if (cmd->args)
			while (cmd->args[i] != NULL)
			{
				printf("args: %s\n", cmd->args[i]);
				i++;
			}
		i = 0;
		if (cmd->redir_out)
			while (cmd->redir_out[i] != NULL)
			{
				printf("redir_out: %s\n", cmd->redir_out[i]);
				i++;
			}
		i = 0;
		if (cmd->redir_append_out)
			while (cmd->redir_append_out[i] != NULL)
			{
				printf("redir_append_out: %s\n", cmd->redir_append_out[i]);
				i++;
			}
		i = 0;
		if (cmd->redir_in)
			while (cmd->redir_in[i] != NULL)
			{
				printf("redir_in: %s\n", cmd->redir_in[i]);
				i++;
			}
		printf("last_out_redir: %s\n", cmd->last_out_redir);
		printf("last_out_redir_type: %d\n", (int)cmd->last_out_redir_type);
		cmd = cmd->next;
	}
}

int		get_command(t_cmd *cmd, char *s)
{
	int end = 1;
	int i = 0;
	char *command = ft_strdup("");
	while(s[i] == ' ')
		i++;
	while(s[i])
	{
		if (s[i] == '\'') //обработка в кавычках, запись в комманд, сдвиг строки
			i += single_quotes(&s[i], &command);
		else if (s[i] == '\"') //обработка в кавычках, запись в комманд, сдвиг строки
			i += double_quotes(&s[i], &command);
		else if (s[i] == ' ') //встречается пробел - пропускаются все в цикле, строка сдвигается
		{
			i++;
			break ;
		}
		else if (s[i] == '|' || s[i] == ';' || s[i] == '<' || s[i] == '>') //в длину не учитываются, далее обработаются в общей функции
			break ;
		else if (s[i] == '\\') //добавится следующий символ, строка сдвинется на 2 символа; нужна проверка на \0
		{
			if (s[i + 1])
			{
				command = add_char(command, s[i + 1]);
				i += 2;
			}
			else
				return (i);
		}
		else
		{
			command = add_char(command, s[i]);
			//printf("command cycle: %s\n", command);
			i++;
		}
	}
	cmd->name = command;
	//printf("command out of cycle: %s\n", cmd->name);
	return (i);
}

int		get_arguments(t_cmd *cmd, char *s)
{
	int end = 1;
	int i = 0;
	char *arg = ft_strdup("");
	while(s[i] == ' ')
		i++;
	while(s[i])
	{
		//printf("each letter of arg: |%c|\n", s[i]);
		if (s[i] == '\'') //обработка в кавычках, запись в комманд, сдвиг строки
		{
			i += single_quotes(&s[i], &arg);
			cmd->args = add_string_to_array(cmd, arg);
			free(arg);
			arg = ft_strdup("");
			while (s[i] == ' ')
				i++;
		}
		else if (s[i] == '\"') //обработка в кавычках, запись в комманд, сдвиг строки
		{
			i += double_quotes(&s[i], &arg);
			cmd->args = add_string_to_array(cmd, arg);
			free(arg);
			arg = ft_strdup("");
			while (s[i] == ' ')
				i++;
		}
		else if (s[i] == ' ') //встречается пробел - пропускаются все в цикле, строка сдвигается
		{
			cmd->args = add_string_to_array(cmd, arg);
			free(arg);
			arg = ft_strdup("");
			while (s[i] == ' ')
				i++;
//			break ;
		}
		else if (s[i] == '|' || s[i] == ';' || s[i] == '<' || s[i] == '>') //в длину не учитываются, далее обработаются в общей функции
			break ;
		else if (s[i] == '\\') //добавится следующий символ, строка сдвинется на 2 символа; нужна проверка на \0
		{
			if (s[i + 1])
			{
				arg = add_char(arg, s[i + 1]);
				i += 2;
			}
			else
			{
				return (i);
			}
		}
		else
		{
			arg = add_char(arg, s[i]);
			//printf("arg cycle: %s\n", arg);
			i++;
			if (!s[i])
			{
				cmd->args = add_string_to_array(cmd, arg);
				free(arg);
				arg = NULL;
			}
		}
	}
	//	printf("command out of cycle: %s\n", (*cmd)->args[0]);
	return (i);
}

void	get_env(char *s, char **parsed)
{

}

//char *parse_it_all(char *el)
//{
//	char *parsed;
//	int i = 0;
//
//	while (el[i])
//	{
//		if (el[i] == '$')
//
//	}
//	return (parsed);
//}

char	**add_line_to_array(char **mod_array, char *line)
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

void parse_input(t_cmd **cmd, char **input, int *i)
{
	int j = *i;
	char *token;
	t_cmd *tmp = ft_lst_new();
	*cmd = tmp;
	while(input[j])
	{
		if (!(ft_strcmp(input[j], ";")))
		{
			j++;
			break ;
		}
		if (!(ft_strcmp(input[j], "|")))
		{
			tmp->pipe_status = true;
			tmp->next = ft_lst_new();
			tmp = tmp->next;
			j++;
			continue ;
		}
//		token = parse_it_all(input[j]);
		if (!tmp->name)
			tmp->name = input[j];
		else if (!(ft_strcmp(input[j], ">")))
		{
			tmp->last_out_redir_type = TRUNC;
			tmp->last_out_redir = ft_strdup(input[j + 1]);
			//add input[j] into struct, not char**, argument to this struct as well
			tmp->redir_out = add_line_to_array(tmp->redir_out, input[j + 1]);
			j++;
		}
		else if (!(ft_strcmp(input[j], ">>")))
		{
			tmp->last_out_redir_type = APPEND;
			tmp->last_out_redir = ft_strdup(input[j + 1]);
			//add input[j] into struct, not char**, argument to this struct as well
			tmp->redir_append_out = add_line_to_array(tmp->redir_append_out, input[++j]);
		}
		else if (!(ft_strcmp(input[j], "<")))
		{
			tmp->redir_in = add_line_to_array(tmp->redir_in, input[++j]);
		}
		else
			tmp->args = add_line_to_array(tmp->args, input[j]);
		j++;
	}
	*i = j;
	// printf("input %d\n\n", *i);
}

// int main(int argc, char **argv)
// {
// 	char *s = NULL;
// 	t_lexer lex;
// 	t_cmd	*cmd = NULL;
// 	int fd = open(argv[1], O_RDONLY);
// 	int i = 0;
// 	int j = 0;
// 	int gnl;
// 	char **res;

// 	while((gnl = get_next_line(fd, &s)) >= 0)
// 	{
// 		i++;
// 		printf("%sTEST %02d: ---> %s%s\n", RED, i, s, NRM);
// 		if (!(res = lexer(s, &lex)))
// 		{
// 			free(s);
// 			s = NULL;
// 			continue ;
// 		}
// 		free(s);
// 		s = NULL;
// 		j = 0;
// 		while (res[j])
// 		{
// 			parse_input(&cmd, res, &j);
// 			print_struct(cmd);
// 		}
// //		ft_remove_char_matrix(res);
// 		if (gnl == 0)
// 			break ;
// 	}

// 	return (0);
// }

//void parse_input(t_cmd **cmd, char *input)
//{
//	char *s = ft_strtrim(input, " ");
//	t_lexer lex;
//	lexer(input, &lex);
////	t_cmd *cmd; //проверить инициализацию HEAD
//	t_cmd *tmp = ft_lst_new(); //next
//	int i = 0;
//
//	while(*s != '\0')
//	{
//		printf("s before cmd: %s\n", s);
//		s += get_command(tmp, s);
//		printf("s after cmd: %s\n", s);
//		if (*s == '<')
//		{
//			tmp->fd_in = 1;
//			s++;
//		}
//		if (*s == '>')
//		{
//			if (*(s + 1) == '>')
//			{
//				tmp->fd_append_out = 1;
//				s += 2;
//			}
//			else
//			{
//				tmp->fd_out = 1;
//				s++;
//			}
//		}
//		if (*s == '|')
//		{
//			tmp->pipe = 1;
//			s++;
//			continue ;
//		}
//		if (*s == ';')
//		{
//			ft_lst_add_back(cmd, tmp);
//			tmp = ft_lst_new();
//			s++;
//			continue ;
//		}
//		while (*s)
//		{
//			printf("s before arg: %s\n", s);
//			int p = get_arguments(tmp, s);
//			printf("offset string p: %d\n", p);
//			s += p;
//			if (*s == '\0')
//				ft_lst_add_back(cmd, tmp);
//			printf("s after arg: %s\n", s);
//			while(*s == ' ')
//				s++;
//			if (*s == '<')
//			{
//				tmp->fd_in = 1;
//				s++;
//			}
//			if (*s == '>')
//			{
//				if (*(s + 1) == '>')
//				{
//					tmp->fd_append_out = 1;
//					s += 2;
//				}
//				else
//				{
//					tmp->fd_out = 1;
//					s++;
//				}
//			}
//			if (*s == '|')
//			{
//				tmp->pipe = 1;
//				s++;
//				continue ;
//			}
//			if (*s == ';')
//			{
//				ft_lst_add_back(cmd, tmp);
//				tmp = ft_lst_new();
//				s++;
//				break ;
//			}
//		}
//	}
////	print_struct(cmd);
////	return(cmd);
//}
//
//int main()
//{
//	char *s;
//	t_cmd *cmd = NULL;
//	int i;
//
//	s = user_input();
//	printf("input string %s\n", s);
//	parse_input(&cmd, s);
//	print_struct(cmd);
//}

//typedef struct s_shell
//{
//	t_cmd *cmd; //list
//	t_env *env;
//	int sigint; //ctrl+c
//	int sigquit; //ctrl
//	char *home;
//	char *user;
//}	t_shell;
