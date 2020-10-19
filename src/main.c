#include <minishell.h>

char	*g_user;
char	*g_home;

void	main_loop(t_env *env)
{
	char	*input;

	input = NULL;
	while (true)
	{
		display_prompt();
		if (!(input = user_input()))
			ft_error(1, "can't read this line");
		printf("input : %s\n", input);
		free(input);
		// parsing
		/*
		execute_input(input, env);
        t_cmd cmd;
        cmd.name = "asd";
        cmd.fd_in= 0;
        cmd.fd_out = 1;
        cmd.next = NULL;
        char *args[] = { "-l", "-a" , NULL };
        cmd.args = args;
		execute_cmd(&cmd, env_list);
		break ; */
	}
}

int		main(int argc, char **argv, char **env)
{
	t_env	*env_list;

	if (argc > 1)
		return (ft_error(1, "too much arguments passed to shell"));
	if (!(env_list = create_env(env)))
		ft_error(ENOMEM, "allocation error");
	signal(SIGINT, signals_handler); // ctrl + c | ctrl + backslash
	init_prompt_vars(&g_user, &g_home, env_list);
	if (argv != NULL)
		main_loop(env_list);
	remove_env(&env_list);
	remove_prompt_vars(g_user, g_home);
	return (0);
}
