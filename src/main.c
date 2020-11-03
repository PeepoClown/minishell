#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;
pid_t	g_pid;

void	test(t_env *env)
{
	t_cmd	*cmd1 = create_cmd(),
			*cmd2 = create_cmd(),
			*cmd3 = create_cmd(),
			*cmd4 = create_cmd(),
			*cmd5 = create_cmd(),
			*cmd6 = create_cmd(),
			*cmd7 = create_cmd(),
			*cmd8 = create_cmd(),
			*cmd9 = create_cmd(),
			*cmd10 = create_cmd();

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

	cmd4->name = ft_strdup("sh");
	cmd4->args = (char**)malloc(sizeof(char*) * 2);
	cmd4->args[0] = ft_strdup("1.sh");
	cmd4->args[1] = NULL;
	cmd4->pipe_status = false;

	cmd5->name = ft_strdup("env");
	cmd5->args = (char**)malloc(sizeof(char*));
	cmd5->args[0] = NULL;
	cmd5->pipe_status = false;

	cmd6->name = ft_strdup("cd");
	cmd6->args = (char**)malloc(sizeof(char*) * 2);
	cmd6->args[0] = ft_strdup("./src");
	cmd6->args[1] = NULL;
	cmd6->pipe_status = false;

	cmd7->name = ft_strdup("env");
	cmd7->args = (char**)malloc(sizeof(char*));
	cmd7->args[0] = NULL;
	cmd7->pipe_status = false;

	cmd8->name = ft_strdup("cat");
	cmd8->args = (char**)malloc(sizeof(char*));
	cmd8->args[0] = NULL;
	cmd8->pipe_status = false;
	cmd8->redir_in = (char**)malloc(sizeof(char*) * 2);
	cmd8->redir_in[0] = ft_strdup("cmd/ft_pwd.c");
	cmd8->redir_in[1] = NULL;

	cmd9->name = ft_strdup("../1.sh");
	cmd9->args = (char**)malloc(sizeof(char*));
	cmd9->args[0] = NULL;
	cmd9->pipe_status = false;

	cmd10->name = ft_strdup("../loop.out");
	cmd10->args = (char**)malloc(sizeof(char*));
	cmd10->args[0] = NULL;
	cmd10->pipe_status = false;

	g_status = handle_cmd(cmd1, env);
	printf("1 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd2, env);
	printf("2 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd3, env);
	printf("3 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd4, env);
	printf("4 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd5, env);
	printf("5 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd6, env);
	printf("6 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd7, env);
	printf("7 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd8, env);
	printf("8 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd9, env);
	printf("9 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd10, env);
	printf("10 : ret : %d\n", g_status);

	remove_cmd(cmd1);
	remove_cmd(cmd2);
	remove_cmd(cmd3);
	remove_cmd(cmd4);
	remove_cmd(cmd5);
	remove_cmd(cmd6);
	remove_cmd(cmd7);
	remove_cmd(cmd8);
	remove_cmd(cmd9);
	remove_cmd(cmd10);
}

void	test1(t_env *env)
{
	t_cmd	*cmd1 = create_cmd(),
			*cmd2 = create_cmd(),
			*cmd3 = create_cmd(),
			*cmd4 = create_cmd(),
			*cmd5 = create_cmd();
	
	cmd1->name = ft_strdup("a=b");
	cmd1->args = (char**)malloc(sizeof(char*) * 3);
	cmd1->args[0] = ft_strdup("ls");
	cmd1->args[1] = ft_strdup("-l");
	cmd1->args[2] = NULL;
	cmd1->pipe_status = false;

	cmd5->name = ft_strdup("_a=    ");
	cmd5->args = (char**)malloc(sizeof(char*));
	cmd5->args[0] = NULL;
	cmd5->pipe_status = false;

	cmd2->name = ft_strdup("export");
	cmd2->args = (char**)malloc(sizeof(char*) * 2);
	cmd2->args[0] = ft_strdup("_a");
	cmd2->args[1] = NULL;
	cmd2->pipe_status = false;

	cmd3->name = ft_strdup("env");
	cmd3->args = (char**)malloc(sizeof(char*));
	cmd3->args[0] = NULL;
	cmd3->pipe_status = false;

	cmd4->name = ft_strdup("export");
	cmd4->args = (char**)malloc(sizeof(char*));
	cmd4->args[0] = NULL;
	cmd4->pipe_status = false;
		
	g_status = handle_cmd(cmd1, env);
	printf("1 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd5, env);
	printf("1.5 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd2, env);
	printf("2 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd3, env);
	printf("3 : ret : %d\n", g_status);

	g_status = handle_cmd(cmd4, env);
	printf("4 : ret : %d\n", g_status);

	remove_cmd(cmd1);
	remove_cmd(cmd5);
	remove_cmd(cmd2);
	remove_cmd(cmd3);
	remove_cmd(cmd4);

}

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
		while (cmd)
		{
			printf("%s\n", cmd->name);
			printf("%s\n", cmd->last_out_redir);
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
		display_prompt();
		if (!(input = user_input()))
			ft_error(NULL, NULL, "can't read this line");
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
