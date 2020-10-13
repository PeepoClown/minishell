#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct	s_cmd
{
	char	*name;
	char	**args;
	int		args_count;
}				t_cmd;

typedef struct	s_main_args
{
	int		argc;
	char	*cmd_name;
	char	**argv;
	char	**env;
	int		env_size;
}				t_main_args;

typedef struct	s_dict_str_str
{
	char	*key;
	char	*value;
}				t_dict_str_str;

typedef struct	s_dict_str_str_array
{
	t_dict_str_str	*dict;
	size_t			size;
}				t_dict_str_str_array;

#endif
