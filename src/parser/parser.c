#include "parser.h"

void	print_struct(t_cmd *cmd)
{
	while(cmd)
	{
		printf("cmd name: %s\n", cmd->name);
		printf("fd_in: %d\n", cmd->fd_in);
		printf("fd_out: %d\n", cmd->fd_out);
		printf("fd_append_out: %d\n", cmd->fd_append_out);
		printf("pipe: %d\n", cmd->pipe);
		int i = 0;
		while (cmd->args[i])
		{
			printf("args: %s\n", cmd->args[i]);
			i++;
		}
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

void parse_input(t_cmd **cmd, char *input)
{
	char *s = ft_strtrim(input, " ");
//	t_cmd *cmd; //проверить инициализацию HEAD
	t_cmd *tmp = ft_lst_new(); //next
	int i = 0;

	while(*s != '\0')
	{
		printf("s before cmd: %s\n", s);
		s += get_command(tmp, s);
		printf("s after cmd: %s\n", s);
		if (*s == '<')
		{
			tmp->fd_in = 1;
			s++;
		}
		if (*s == '>')
		{
			if (*(s + 1) == '>')
			{
				tmp->fd_append_out = 1;
				s += 2;
			}
			else
			{
				tmp->fd_out = 1;
				s++;
			}
		}
		if (*s == '|')
		{
			tmp->pipe = 1;
			s++;
			continue ;
		}
		if (*s == ';' || *s == 0)
		{
			ft_lst_add_back(cmd, tmp);
			printf("%s\n", (*cmd)->name);
			tmp = ft_lst_new();
			s++;
			continue ;
		}
		while (*s)
		{
			printf("s before arg: %s\n", s);
			int p = get_arguments(tmp, s);
			printf("offset string p: %d\n", p);
			s += p;
			if (*s == '\0')
				ft_lst_add_back(cmd, tmp);
			printf("s after arg: %s\n", s);
			while(*s == ' ')
				s++;
			if (*s == '<')
			{
				tmp->fd_in = 1;
				s++;
			}
			if (*s == '>')
			{
				if (*(s + 1) == '>')
				{
					tmp->fd_append_out = 1;
					s += 2;
				}
				else
				{
					tmp->fd_out = 1;
					s++;
				}
			}
			if (*s == '|')
			{
				tmp->pipe = 1;
				s++;
				continue ;
			}
			if (*s == ';' || *s == 0)
			{
				ft_lst_add_back(cmd, tmp);
				tmp = ft_lst_new();
				printf("===================%s\n", (*cmd)->args[0]);
				s++;
				break ;
			}
		}
	}
//	print_struct(cmd);
//	return(cmd);
}

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