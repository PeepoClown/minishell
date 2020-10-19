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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
//# include <limits.h>

#include <linux/limits.h>

extern char *g_user;
extern char *g_home;

void	signals_handler(int sig);

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
void            del_env_item(t_env *env);
void			del_env(t_env **env, const char *key);
void            remove_env(t_env **env);
char			*get_env_value(t_env *env, const char *key);
void			print_env(t_env *env, int fd_out);
void			print_env_export(t_env *env, int fd_out);
void			sort_env(t_env **env);

/*
** prompt and input to shell
*/

void            init_prompt_vars(char **user, char **home, t_env *env);
void			display_prompt(void);
void            remove_prompt_vars(char *user, char *home);
char	        *user_input(void);

/*
** structure of command
*/

typedef struct	s_cmd
{
    char			*name;
    char			**args;
    int				fd_out;
    int				fd_in;
    struct s_cmd	*next;
}				t_cmd;

/*
** builtin commands
*/

typedef struct	s_builtin
{
    char    *cmd;
    int     (*func)(t_cmd *, t_env *);
}				t_builtin;

int			ft_echo(t_cmd *cmd, t_env *env);
int		       ft_cd(t_cmd *cmd, t_env *env);
int		      ft_pwd(t_cmd *cmd, t_env *env);
int		    ft_export(t_cmd *cmd, t_env *env);
int		ft_env(t_cmd *cmd, t_env *env);
int			ft_unset(t_cmd *cmd, t_env *env);
int		ft_exit(t_cmd *cmd, t_env *env);
int		execute(t_cmd *cmd, t_env *env);




int     execute_cmd(t_cmd *cmd, t_env *env);











void			error_cmd(const char *cmd, const char *error,
                          const char *desc);

int		ft_error(int status, const char *error);


#endif
