#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include "../lib/lib.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
//# include <limits.h>
#include <linux/limits.h> // delete this header

/*
** interface for env vars
*/

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env			*create_env_item(const char *line);
t_env			*create_env(char **env_vars);
void			add_env(t_env **env, const char *line);
void			del_env(t_env **env, const char *key);
char			*get_env_value(t_env *env, const char *key);
void			print_env(t_env *env, int fd_out);
void			print_env_export(t_env *env, int fd_out);
void			sort_env(t_env **env);


void			display_prompt(t_env *env);
char	*user_input(void);


/*
** builtin commands
*/

typedef struct	s_cmd
{
	char			*name;
	char			**args;
	int				fd_out;
	int				fd_in;
	struct s_cmd	*next;
}				t_cmd;

void			error_cmd(const char *cmd, const char *error,
							const char *desc);

int				ft_echo(t_cmd *cmd, t_env *env);
int		ft_cd(t_cmd *cmd, t_env *env);
int		ft_pwd(t_cmd *cmd, t_env *env);
int		ft_export(t_cmd *cmd, t_env *env);

#endif
