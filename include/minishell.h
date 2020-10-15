#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include "../lib/lib.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
#include <linux/limits.h> // delete this header
# include <string.h>
# include <stdbool.h>

/*
** interface for env vars
*/

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env			*create_env(char **env_vars);
t_env			*create_env_item(const char *line);
char			*get_env_value(t_env *env, char *key);
void			sort_env(t_env **env);
void			print_env_export(t_env *env, int fd_out);

/*
** builtin commands
*/

void			error_cmd(const char *cmd, const char *error,
							const char *desc);

int				ft_pwd(t_env *env, int fd_out, int fd_in, char **args);
int				ft_cd(t_env *env, int fd_out, int fd_in, char **args);
int				ft_echo(t_env *env, int fd_out, int fd_in, char **args);
int				ft_export(t_env *env, int fd_out, int fd_in, char **args);

#endif
