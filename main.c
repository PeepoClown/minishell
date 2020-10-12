#include "minishell.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t count;

	count = 0;
	while (*(str + count))
		count++;
	return (count);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	if (s)
		write(1, (char*)s, ft_strlen(s));
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*copy;

	copy = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(str))
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	if (ft_strlen((char*)s) <= start)
		return (ft_strdup(""));
	size = ft_strlen((char*)s + start);
	if (len > size)
		len = size;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(str + i) = *(s + start + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (s1[i] - s2[i]);
}

int		ft_find_first_of(const char *str, char sym)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sym)
			return (i);
		i++;
	}
	return (-1);
}

char	**copy_char_matrix(char **matrix, int rows)
{
	char	**copy;
	int		i;

	i = 0;
	if (!(copy = (char**)malloc(sizeof(char*) * (rows + 1))))
		return (NULL);
	while (i < rows)
	{
		if (!(copy[i] = ft_strdup(matrix[i])))
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_main_args	*copy_main_args(int argc, char **argv, char **env)
{
	t_main_args	*main_args;
	int			env_size;

	if (!(main_args = (t_main_args*)malloc(sizeof(t_main_args))))
		return (NULL);
	main_args->argc = argc;
	if (!(main_args->cmd_name = ft_strdup(argv[0])))
		return (NULL);
	if (!(main_args->argv = copy_char_matrix(argv + 1, argc - 1)))
		return (NULL);
	env_size = 0;
	while (env[env_size] != NULL)
		env_size++;
	main_args->env_size = env_size;
	if (!(main_args->env = copy_char_matrix(env, env_size)))
		return (NULL);
	return (main_args);
}

void	print_main_args(t_main_args *main_args)
{
	printf("argc : %d\ncommand name : %s\n", main_args->argc, main_args->cmd_name);
	char **tmp = main_args->argv;
	while (*tmp != NULL)
	{
		printf("%s\n", *tmp);
		tmp++;
	}
	printf("count of env vars : %d\n", main_args->env_size);
	tmp = main_args->env;
	while (*tmp != NULL)
	{
		printf("%s\n", *tmp);
		tmp++;
	}
}

t_dict_str_str_array	*parse_env_vars(t_main_args *main_args)
{
	t_dict_str_str_array	*dict;
	int						i;
	int						delim_pos;

	if (!(dict = (t_dict_str_str_array*)malloc(sizeof(t_dict_str_str_array))))
		return (NULL);
	if (!(dict->dict = (t_dict_str_str*)malloc(sizeof(t_dict_str_str) *
		main_args->env_size)))
		return (NULL);
	dict->size = main_args->env_size;
	i = 0;
	while (i < main_args->env_size)
	{
		delim_pos = ft_find_first_of(main_args->env[i], '=');
		if (!(dict->dict[i].key = ft_substr(main_args->env[i], 0, delim_pos)))
			return (NULL); // delete previous
		if (!(dict->dict[i].value = ft_substr(main_args->env[i], delim_pos + 1,
			ft_strlen(main_args->env[i]) - delim_pos - 1)))
			return (NULL); // delete previous
		i++;
	}
	return (dict);
}

char	*get_dict_value(t_dict_str_str_array *dict, const char *key)
{
	size_t	i;

	i = 0;
	while (i < dict->size)
	{
		if (ft_strcmp(dict->dict[i].key, key) == 0)
			return (dict->dict[i].value);
		i++;
	}
	return ("");
}

void	print_dict(t_dict_str_str_array *dict)
{
	int		i;

	i = 0;
	while (i < dict->size)
	{
		printf("key : |%s| --- value : |%s|\n", dict->dict[i].key, dict->dict[i].value);
		i++;
	}
}

char	*cut_home_path(t_dict_str_str_array *dict)
{
	char	*path;
	char	*home_path;
	char	*path_with_home;
	int		i;
	int		j;

	path = ft_strdup(get_dict_value(dict, "PWD"));
	home_path = ft_strdup(get_dict_value(dict, "HOME"));
	path_with_home = ft_substr(path, 0, ft_strlen(home_path));
	if (ft_strcmp(path_with_home, home_path) == 0)
	{
		path_with_home = (char*)malloc(sizeof(char) * (ft_strlen(path) -
			ft_strlen(home_path) + 2));
		path_with_home[0] = '~';
		i = ft_strlen(home_path);
		j = 1;
		while (i < ft_strlen(path))
			path_with_home[j++] = path[i++];
		return (path_with_home);
	}
	else
		return (path);
}

void	display_prompt(const char *prompt, t_dict_str_str_array *dict)
{
	char	*path;
	char	*user;

	user = ft_strdup(get_dict_value(dict, "USER"));
	path = cut_home_path(dict);
	write(1, "\e[1;35m", 8);
	ft_putstr(user);
	write(1, "\e[0m:", 6);
	write(1, "\e[1;33m", 8);
	ft_putstr(path);
	write(1, "\e[0m\n", 6);
	ft_putstr(prompt);
}

char	*add_to_str(char *str, char c)
{
	int		i = 0;
	char	*res;

	res = (char*)malloc((ft_strlen(str) + 2) * sizeof(char));
	while (i < ft_strlen(str))
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

char	*user_input(void)
{
	char	*input;
	char	buff[1];
	int		read_res;

	input = ft_strdup("");
	while ((read_res = read(0, buff, 1)) != 0)
	{
		if (buff[0] == '\n')
			break ;
		input = add_to_str(input, buff[0]);
	}
	add_to_str(input, '\0');
	if (read < 0)
	{
		free(input);
		input = NULL;
	}
	return (input);
}

void	sig_handle(int sig_code)
{
	if (sig_code == SIGINT)
	{
		ft_putstr("\n$> ");
		signal(SIGINT, &sig_handle); //SIGINT handle
	}
}

int		main(int argc, char **argv, char **env)
{
	t_main_args	*main_args;

	main_args = copy_main_args(argc, argv, env);
	if (!main_args)
		printf("Alloc error!\n");
	//print_main_args(main_args);
	t_dict_str_str_array *dict = parse_env_vars(main_args);
	//print_dict(dict);
	char *input;
	while (true)
	{
		display_prompt("$> ", dict);
		signal(SIGINT, &sig_handle); //SIGINT handle
		input = user_input();
		printf("user input : %s\n", input);
		//parsing input
		//trim by ';'
	}
	return (0);
}
