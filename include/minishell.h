/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:06:32 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 21:52:49 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define READ_END	0
# define WRITE_END	1

extern char		*g_user;
extern char		*g_home;
extern char		*g_home_const;
extern bool		g_is_copy_rm;
extern int		g_status;
extern pid_t	g_pid;
extern bool		g_input_start;
extern int		g_fd_out;
extern int		g_fd_in;

/*
** interface for env vars
*/

typedef	enum	e_hidden_status
{
	VISIBLE = 0,
	HIDDEN,
	EXPORT_VIS,
	ENV_VIS
}				t_hidden_status;

typedef	struct	s_env
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
void			set_env_hidden(t_env *env, const char *key,
								t_hidden_status status);
bool			check_env_key(t_env *env, const char *key);
void			print_env(t_env *env, int fd_out);
void			print_env_export(t_env *env, int fd_out);
void			sort_env(t_env **env);
char			**get_env_matrix(t_env *env);
t_env			*copy_env(t_env *env);
void			set_path_env_var(t_env *env, const char *path);
void			set_oldpwd_null(t_env *env);

/*
** structure of command
*/

typedef struct	s_builtin
{
	char	*cmd;
	int		(*func)(void*, t_env*);
}				t_builtin;

typedef enum	e_out_redir
{
	NONE = 0,
	TRUNC,
	APPEND
}				t_out_redir;

typedef	struct	s_cmd
{
	char			*name;
	char			**args;
	int				fd_out;
	int				fd_in;
	char			**redir_out;
	char			**redir_append_out;
	char			*last_out_redir;
	t_out_redir		last_out_redir_type;
	char			**redir_in;
	bool			pipe_status;
	int				pipe[2];
	t_builtin		*builtin;
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
	char	match_quote;
	char	unexp_token;
	char	**tokens;
}				t_lexer;

/*
** input syntax check
*/

char			**lexer(char *s, t_lexer *lexer);
void			lexer_init(t_lexer *lexer);
int				unexpected_token(char unexpected);
int				unexpected_redirects(void);
int				unexpected_eof(char match_quote);
int				quote_pair(char *s, char quote, int *error);
int				spaces(char *s);
int				token_quotes(t_lexer *lexer, char *s, char **current_token);
int				token_separators(t_lexer *lexer, char *s, char **current_token);
int				token_redirects(t_lexer *lexer, char *s, char **current_token);
int				lexer_backslash(char *s, t_lexer *lexer, char **current_token);
void			lexer_env(t_lexer *lexer, char *s, char **current_token);
int				lexer_symbols(char *s, t_lexer *lexer, char **current_token);
char			**check_last_elem(char *current_token);

/*
** input parsing
*/

void			parse_input(t_cmd **cmd, char **input, int *i, t_env *env);
void			fill_structure(t_cmd **tmp, char **input, t_env *env, int *j);
int				fill_struct_redirects(t_cmd **tmp, char **input, t_env *env,
										int *i);
char			**extend_arr(char **mod_array, char *line);
char			*parse_tokens(char *tokens, t_env *env);
void			parsing(char *token, char **parsed, t_env *env);

/*
** processing quotes
*/

int				replace_env(char *s, t_env *env, char **token, int flag);
int				double_quotes(char *s, char **token, t_env *env);
int				single_quotes(char *s, char **token);
int				env_single_quote(char *s, char **token);
int				env_status(char *s, int i, char **token, char *tmp);
char			escape_char(char c);

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
void			remove_prompt_vars(char *user, char *home, char *home_const);
char			*user_input(void);
void			ft_remove_cmd(t_cmd *cmd);

/*
** utilities and auxiliaries
*/

char			*add_char(char *s, char c);
t_cmd			*ft_lst_new();
int				array_size(char **array);
char			*combine_tokens(char *token, char c);

#endif
