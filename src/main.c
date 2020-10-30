#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;
pid_t	g_pid;

void	test(t_env *env)
{
	t_cmd	*cmd1 = create_cmd(),
			*cmd2 = create_cmd(),
			*cmd3 = create_cmd();

	cmd1->name = ft_strdup("ls");
	cmd1->args = (char**)malloc(sizeof(char*) * 2);
	cmd1->args[0] = ft_strdup("-l");
	cmd1->args[1] = NULL;
	cmd1->pipe_status = true;

	cmd2->name = ft_strdup("grep");
	cmd2->args = (char**)malloc(sizeof(char*) * 2);
	cmd2->args[0] = ft_strdup("M");
	cmd2->args[1] = NULL;
	cmd2->pipe_status = true;
	cmd2->redir_out = (char**)malloc(sizeof(char*) * 2);
	cmd2->redir_out[0] = ft_strdup("1.text");
	cmd2->redir_out[1] = NULL;
	cmd2->last_out_redir = *(cmd2->redir_out);
	cmd2->last_out_redir_type = TRUNC;

	cmd3->name = ft_strdup("cat");
	cmd3->args = (char**)malloc(sizeof(char*) * 2);
	cmd3->args[0] = ft_strdup("-e");
	cmd3->args[1] = NULL;
	cmd3->pipe_status = false;

	g_status = handle_cmd(cmd1, env);
	printf("1 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd2, env);
	printf("2 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd3, env);
	printf("3 : ret : %d\n", g_status);

	remove_cmd(cmd1);
	remove_cmd(cmd2);
	remove_cmd(cmd3);
}

static	void	minishell(t_env *env)
{
	char	*input;
	t_cmd	*cmd;

	while (true)
	{
		test(env);
		break ;


		input = NULL;
		display_prompt();
		if (!(input = user_input()))
			ft_error(NULL, NULL, "can't read this line");
		free(input);
		// break ;




		// validate all line
		while (*input != '\0')
		{
			// create command
			// parse_input(&cmd, input);
			if (cmd != NULL)
				g_status = handle_cmd(cmd, env);
			// remove_cmd(cmd);
			*input = 0;
			printf("ret : %d\n", g_status);
		}
		free(input);
		break ;
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
