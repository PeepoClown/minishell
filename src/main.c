#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;

void	main_loop(t_env *env)
{
	char	*input;
	t_cmd	cmd;

	input = NULL;
	while (true)
	{
		display_prompt();
		if (!(input = user_input()))
			ft_error(NULL, NULL, "can't read this line");
		printf("input : %s\n", input);
		parse_input(&cmd, input);
		free(input);
		// parsing
		// execute_input(input, env) for all list of commands
		t_cmd cmd;
		cmd.name = ft_strdup("./1.sh");
		cmd.fd_out = 1;
		cmd.fd_in = 0;
		char *args[] = { NULL };
		cmd.args = args;
		execute_cmd(&cmd, env);
		printf("ret : %d\n", g_status);
		free(cmd.name);
		break ;
	}
}

int		main(int argc, char **argv, char **env)
{
	t_env	*env_list;

	if (argc > 1)
		ft_error(NULL, NULL, "too much arguments passed to shell");
	alloc_check(env_list = create_env(env));
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
	init_prompt_vars(env_list);
	if (argv != NULL)
		main_loop(env_list);
	remove_env(&env_list);
	remove_prompt_vars(g_user, g_home);
	return (0);
}
