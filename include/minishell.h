#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include "../lib/lib.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define READ_END 0
# define WRITE_END 1

extern char		*g_user;
extern char		*g_home;
extern int		g_status;
extern pid_t	g_pid;
extern bool		g_input_start;

/*
** interface for env vars
*/

typedef enum	e_hidden_status
{
	VISIBLE = 0,
	HIDDEN,
	EXPORT_VIS,
	ENV_VIS
}				t_hidden_status;

typedef struct	s_env
{
	char			*key;
	char			*value;
	t_hidden_status	is_hidden;
	struct s_env	*next;
}				t_env;

t_env			*create_env_item(const char *line);
t_env			*create_env(char **env_vars);
void			add_env(t_env **env, const char *line);
void			add_to_env(t_env *env, const char *line);
void			del_env_item(t_env *env);
void			del_env(t_env **env, const char *key);
void			remove_env(t_env **env);
char			*get_env_value(t_env *env, const char *key);
void			change_env_value(t_env *env, const char *line);
void			set_env_hidden(t_env *env, const char *key, t_hidden_status status);
bool			check_env_key(t_env *env, const char *key);
void			print_env(t_env *env, int fd_out);
void			print_env_export(t_env *env, int fd_out);
void			sort_env(t_env **env);
char			**get_env_matrix(t_env *env);
t_env			*copy_env(t_env *env);
void			set_path_env_var(t_env *env, const char *path);

/*
** structure of command
*/

typedef struct	s_cmd
				t_cmd;

typedef struct	s_builtin
{
	char	*cmd;
	int		(*func)(t_cmd *, t_env *);
}				t_builtin;

typedef enum	e_out_redir
{
	NONE = 0,
	TRUNC,
	APPEND
}				t_out_redir;

typedef struct	s_cmd
{
	char		*name;
	char		**args;
	int			fd_out;
	int			fd_in;
	char		**redir_out;
	char		**redir_append_out;
	char		*last_out_redir;
	t_out_redir	last_out_redir_type;
	char		**redir_in;
	bool		pipe_status;
	int			pipe[2];
	t_builtin	*builtin;
	struct s_cmd	*next;
}				t_cmd;

/*
** structure of lexer
*/

typedef struct	s_lexer
{
	int		i;
	int		error;
	int		token_len;
	char 	match_quote;
	char 	unexp_token;
	char 	**tokens;
}				t_lexer;

/*
** input syntax check
*/

char			**lexer(char *s, t_lexer *lexer);

/*
** input parsing
*/

void			parse_input(t_cmd **cmd, char **input, int *i, t_env *env);
int				get_arguments(t_cmd *cmd, char *s);
int				get_command(t_cmd *cmd, char *s);
char			*parse_tokens(char *tokens, t_env *env);
int				replace_env(char *s, t_env *env, char **token);

/*
** processing quotes
*/

int				double_quotes(char *s, char **token, t_env *env);
int				single_quotes(char *s, char **token);

/*
** builtin commands & other programms
*/

int				ft_echo(t_cmd *cmd, t_env *env);
int				ft_cd(t_cmd *cmd, t_env *env);
int				ft_pwd(t_cmd *cmd, t_env *env);
int				ft_export(t_cmd *cmd, t_env *env);
int				ft_env(t_cmd *cmd, t_env *env);
int				ft_unset(t_cmd *cmd, t_env *env);
int				ft_exit(t_cmd *cmd, t_env *env);

int				handle_cmd(t_cmd *cmd, t_env *env);
void			validate_hidden_env(t_env *env, t_cmd *cmd);
bool			validate_output_redirects(t_cmd *cmd);
bool			validate_input_redirects(t_cmd *cmd);
t_builtin		*get_builtin(const char *cmd_name);
bool			validate_non_builtin_cmd(t_cmd *cmd, t_env *env);
char			*get_programm_path(const char *cmd, char **paths);
char			**get_args_matrix(const char *cmd, char **args);
int				open_output_redirect(t_cmd *cmd, int fd_out);
int				open_input_redirect(t_cmd *cmd, int fd_in);
int				execute_programm(t_cmd *cmd, t_env *env);

/*
** shell utils
*/

void			ft_error(const char *cmd, const char *error, const char *desc);
void			alloc_check(void *ptr);
int				programm_error(const char *cmd);
void			signals_handler(int sig);
void			init_prompt_vars(t_env *env);
void			display_prompt(void);
void			remove_prompt_vars(char *user, char *home);
char			*user_input(void);
t_cmd			*create_cmd(void);
void			remove_cmd(t_cmd *cmd);

/*
** utilities and auxiliaries
*/

char			*add_char(char *s, char c);
t_cmd			*ft_lst_new();
void			ft_lst_add_back(t_cmd **cmd, t_cmd *new);
int				array_size(char **array);
int				free_array(char **array);
char			**add_string_to_array(t_cmd *cmd, char *arg);
char			**add_token_to_array(t_lexer *lexer, char *arg, int i);
char			*combine_tokens(char *token, char c);

#endif
