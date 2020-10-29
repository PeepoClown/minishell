#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;

void	simulate_parse(t_cmd *cmd)
{
	cmd->name = ft_strdup("ls");
	cmd->args = (char**)malloc(sizeof(char*) * 2);
	cmd->args[0] = ft_strdup("-l");
	cmd->args[1] = NULL;
	cmd->pipe_status = false;
	cmd->redir_in = NULL;
	cmd->redir_append_out = NULL; // (char**)malloc(sizeof(char*) * 2);
	// cmd->redir_append_out[0] = ft_strdup("/var/2.text");
	// cmd->redir_append_out[1] = NULL;
	cmd->redir_out = NULL; // (char**)malloc(sizeof(char*) * 2);
	// cmd->redir_out[0] = ft_strdup("1.text");
	// cmd->redir_out[1] = NULL;
	cmd->lst_out_red = NULL; // *(cmd->redir_out);
	cmd->is_lst_out_red_append = false;
}

void	test(t_env *env)
{
	t_cmd cmd1, cmd2;

	cmd1.name = ft_strdup("ls");
	cmd1.args = (char**)malloc(sizeof(char*) * 2);
	cmd1.args[0] = ft_strdup("-l");
	cmd1.args[1] = NULL;
	cmd1.pipe_status = true;
	cmd1.redir_in = NULL;
	cmd1.redir_append_out = NULL;
	cmd1.redir_out = NULL;
	cmd1.lst_out_red = NULL;
	cmd1.is_lst_out_red_append = false;

	cmd2.name = ft_strdup("cat");
	cmd2.args = (char**)malloc(sizeof(char*) * 2);
	cmd2.args[0] = ft_strdup("-e");
	cmd2.args[1] = NULL;
	cmd2.pipe_status = false;
	cmd2.redir_in = NULL;
	cmd2.redir_append_out = NULL;
	cmd2.redir_out = NULL;
	cmd2.lst_out_red = NULL;
	cmd2.is_lst_out_red_append = false;

	g_status = handle_cmd(&cmd1, env);
	printf("ret : %d\n", g_status);

	g_status = handle_cmd(&cmd2, env);
	printf("ret : %d\n", g_status);
}

static	void	minishell(t_env *env)
{
	char	*input;
	t_cmd	*cmd;

	while (true)
	{
		test(env);
		break;
		input = NULL;
		display_prompt();
		if (!(input = user_input()))
			ft_error(NULL, NULL, "can't read this line");
		// validate all line
		while (*input != '\0')
		{
			cmd = (t_cmd*)malloc(sizeof(t_cmd));
			simulate_parse(cmd); //parse_input(&cmd, input);
			if (cmd != NULL)
				g_status = handle_cmd(cmd, env);
			// remove_cmd(cmd);
			// sig handle
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
