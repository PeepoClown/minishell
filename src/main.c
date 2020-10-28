#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;

static	void	minishell(t_env *env)
{
	char	*input;
	t_cmd	*cmd;

	while (true)
	{
		input = NULL;
		display_prompt();
		if (!(input = user_input()))
			ft_error(NULL, NULL, "can't read this line");
		// validate all line
		while (*input != '\0')
		{
			parse_input(&cmd, input);
			if (cmd != NULL)
				execute_cmd(cmd, env);
			// remove_cmd(cmd);
			// sig handle
		}
		free(input);
		printf("ret : %d\n", g_status);
	}
}

int				main(int argc, char **argv, char **env)
{
	t_env	*env_list;

	if (argc > 1)
		ft_error(NULL, NULL, "too much arguments passed to shell");
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
