#include "../../include/minishell.h"
#include "../../lib/lib.h"

//char	**split_input(char *input)
//{
//	char	**commands;
//
//	commands = ft_split(input, ';');
//	return (commands);
//}
//
//void	parse_input(t_cmd *cmd, char *input)
//{
//	char	*s;
//	char	**commands;
//	int		i;
//
//	name_len = 0;
//	i = -1;
//	commands = split_input(input); //split by blocks
//	while (commands[++i] != NULL)
//	{
//		s = ft_strtrim(commands[i], " ");
//		while (s[name_len] != ' ')
//			name_len++;
//		cmd->name = ft_substr(s, 0, name_len);
//		cmd->args = ft_split(s + name_len, ' ');
//	}
//}

typedef struct	s_quote
{
	int inside_d;
	int inside_s;
	int odq; //open double
	int cdq; //close double
	int osq; //open single
	int csq; //close singe
}				t_quote;

//void	count_double_quote(char *s)
//{
//
//}
void	quote_init(t_quote *q)
{
	q->inside_d = 0;
	q->inside_s = 0;
	q->odq = 0;
	q->cdq = 0;
	q->osq = 0;
	q->csq = 0;
}

int		cmd_name(t_cmd *cmd, char *s)
{
	int	i;
	int	j;
	t_quote q;
	int	end;

	i = 0;
	end = 1;
	quote_init(&q);
	while (end && s[i] != '\0') //имя команды
	{
		j = 0;
//		while (s[i] != '\'' && s[i] != '"' && s[i] != ' ' && s[i] != '\0')
		while (!q.inside_d || !q.inside_s || s[i] != '\0')
		{
			if (s[i] == '\\')
				i++;
//			i++;
			if (s[i] == ' ')
			{
				end = 0;
				break ;
			}
			if (s[i] == '\'')
				q.inside_s = 1;
			if (s[i] == '"')
				q.inside_d = 1;
			i++;
		}
		cmd->name = ft_substr(s, 0, i);
		printf("cmd join: %s\n", cmd->name);
		if (q.inside_d == 1)
		{
			i++;
			j = i;
			while(s[j] != '"' && s[j] != '\0')
			{
				j++;
				if (s[j] == '"')
					q.inside_d = 2;
			}
			cmd->name = ft_strjoin(cmd->name, ft_substr(s, i, j));
			i += j + 1;
		}
		i++;
		if (q.inside_d == 2)
			break ;
	}
//	while(s[i] != '\0' && !q.cdq)
//	{
//		if (s[i] == '"')
//			q.cdq = 1;
//	}

	while (s[i] == ' ') //пропуск пробелов после команды
		i++;
	return (i);
}

//void	parse_input(t_cmd *cmd, char *input)
//{
//	char	*s;
//	int		i;
//	int		open_single_quote;
//	int		close_single_quote;
//	int		open_double_quote;
//	int		close_double_quote;
//	int		backslash;
//	char	**split;
//	t_cmd	*tmp;
//	int		arg_start;
//	int		arg_end;
//
//	s = ft_strtrim(input, " "); //убираем свободные пробелы с обеих сторон
//	/* флаги */
//	i = -1;
//	open_double_quote = 0;
//	close_double_quote = 0;
//	backslash = 0;
//	tmp = cmd;
//	arg_start = 0;
//	arg_end = 0;
//
//	while(s[++i] != '\0')
//	{
//		printf("string before cmd %s\n", s);
//		i += cmd_name(tmp, s + i);
//		s += i;
//		printf("string after cmd %s\n", s);
//		tmp->args = ft_split(s, ' ');
//		break ;
////		count_double_quote(s + i);
////		arg_start = i;
////		arg_end = arg_start;
////		while (s[i] != ' ' && !close_single_quote && !close_double_quote)
////		{
////			if (s[i] == '\0') //
////				break ; //конец инпута
////			if (s[i] == ';' && !backslash)
////				break ; //конец команды
////			if (s[i] == '\\' && !open_single_quote && !open_double_quote)
////				backslash = 1;
////			while (s[i] != '"' && s[i] != '\0')
////				arg_end++;
////		}
////
////		if (s[i] == '\\')
////			backslash = 1; //continue
////		if (s[i] == '"' && backslash == 1)
////			ft
//
//	}
//}

#include <stdio.h>
#include <fcntl.h>

//char	**add_str_to_array(char **array)
//{
//
//}

int main()
{
	t_cmd cmd;
	int i = 0;
	char *s = user_input();
	char **array = (char **)malloc(sizeof(char *));
	array[0] = (char *)malloc(sizeof(char));
	*array[0] = '\0';

	printf("input string %s\n", s);
	parse_input(&cmd, s);
//	while(s[i] != '\0')
//	{
//		while(s[i] != ' ' && s[i])
//		{
//
//		}
//	}



	printf("cmd: %s\n", cmd.name);
	i = 0;
	while(cmd.args[i])
	{
		printf("args: %s\n", cmd.args[i]);
		i++;
	}
	return (0);
}
