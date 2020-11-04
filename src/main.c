#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;
pid_t	g_pid;
bool	input_start;

static	int		main_loop(t_env *env, char *input)
{
	t_lexer	lex;
	char	**tokens;
	int		i;
	t_cmd	*cmd;

	if (!(tokens = lexer(input, &lex)))
		return (0);
	i = 0;
	cmd = NULL;
	while (tokens[i] != NULL)
	{
		parse_input(&cmd, tokens, &i, env);
		while (cmd != NULL)
		{
			g_status = handle_cmd(cmd, env);
			cmd = cmd->next;
		}
		// remove cmd
	}
	return (1);
}

static	void	minishell(t_env *env)
{
	char	*input;

	while (true)
	{
		input = NULL;
		g_pid = 0;
		display_prompt();
		if (!(input = user_input()))
		{
			ft_error(NULL, NULL, "can't read this line");
			continue ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		if (!main_loop(env, input))
		{
			ft_putstr_fd("materi svoey takoe napishi\n", 2);
			free(input);
			continue ;
		}
		free(input);
	}
}

int				main(int argc, char **argv, char **env)
{
	t_env	*env_list;

	if (argc > 1)
	{
		ft_error(NULL, NULL, "too much arguments passed to shell");
		return (0); // 1 ???
	}
	alloc_check(env_list = create_env(env));
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
	init_prompt_vars(env_list);
	if (argv != NULL)
		minishell(env_list);
	remove_env(&env_list);
	remove_prompt_vars(g_user, g_home);
	return (0);
}
