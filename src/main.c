#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;
pid_t	g_pid;

void	test(t_env *env)
{
	t_cmd cmd1, cmd2, cmd3;

	// cmd1.name = ft_strdup("./loop");
	// cmd1.args = (char**)malloc(sizeof(char*) * 1);
	// //cmd1.args[0] = ft_strdup("-l");
	// cmd1.args[0] = NULL;
	// cmd1.pipe_status = false;
	// cmd1.redir_in = NULL;
	// cmd1.redir_append_out = NULL;
	// cmd1.redir_out = NULL;
	// cmd1.last_out_redir = NULL;
	// cmd1.is_last_out_redir_default = true;

	cmd1.name = ft_strdup("echo");
	cmd1.args = (char**)malloc(sizeof(char*) * 2);
	cmd1.args[0] = ft_strdup("asd");
	cmd1.args[1] = NULL;
	cmd1.pipe_status = false;
	cmd1.redir_in = NULL;
	cmd1.redir_append_out = NULL;
	char *redir_out[] = { "/usr/1", NULL };
	cmd1.redir_out = redir_out;
	cmd1.last_out_redir = *redir_out;
	cmd1.is_last_out_redir_default = true;

	cmd2.name = ft_strdup("grep");
	cmd2.args = (char**)malloc(sizeof(char*) * 2);
	cmd2.args[0] = ft_strdup("h");
	cmd2.args[1] = NULL;
	cmd2.pipe_status = true;
	cmd2.redir_in = NULL;
	cmd2.redir_append_out = NULL;
	char *redir_out2[] = { "1.text", NULL };
	cmd2.redir_out = redir_out2;
	cmd2.last_out_redir = *redir_out;
	cmd2.is_last_out_redir_default = true;

	cmd3.name = ft_strdup("cat");
	cmd3.args = (char**)malloc(sizeof(char*) * 2);
	cmd3.args[0] = ft_strdup("-e");
	cmd3.args[1] = NULL;
	cmd3.pipe_status = false;
	cmd3.redir_in = NULL;
	cmd3.redir_append_out = NULL;
	cmd3.redir_out = NULL;
	cmd3.last_out_redir = NULL;
	cmd3.is_last_out_redir_default = true;

	g_status = handle_cmd(&cmd1, env);
	printf("1 : ret : %d\n", g_status);

	// g_status = handle_cmd(&cmd2, env);
	// printf("2 : ret : %d\n", g_status);

	// g_status = handle_cmd(&cmd3, env);
	// printf("3 : ret : %d\n", g_status);

	int i;
	// free(cmd1.name);
	// i = 0;
	// while (cmd1.args[i] != NULL)
	// 	free(cmd1.args[i++]);
	// free(cmd1.args);

	free(cmd2.name);
	i = 0;
	while (cmd2.args[i] != NULL)
		free(cmd2.args[i++]);
	free(cmd2.args);

	free(cmd3.name);
	i = 0;
	while (cmd3.args[i] != NULL)
		free(cmd3.args[i++]);
	free(cmd3.args);
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
