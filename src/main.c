#include <minishell.h>

char	*g_user;
char	*g_home;
int		g_status;

void	simulate_parse1(t_cmd *cmd)
{
	cmd->name = ft_strdup("ls");
	cmd->args = (char**)malloc(sizeof(char*) * 2);
	cmd->args[0] = ft_strdup("-l");
	cmd->args[1] = NULL;
	cmd->pipe_status = true;
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

void	simulate_parse2(t_cmd *cmd)
{
	cmd->name = ft_strdup("grep");
	cmd->args = (char**)malloc(sizeof(char*) * 2);
	cmd->args[0] = ft_strdup("M");
	cmd->args[1] = NULL;
	cmd->pipe_status = false;
	cmd->redir_in = NULL;
	cmd->redir_append_out = NULL;
	cmd->redir_out = NULL;
	cmd->lst_out_red = NULL;
	cmd->is_lst_out_red_append = false;
}

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
		int i = 0;
		//while (*input != '\0')
		while (i < 2)
		{
			cmd = (t_cmd*)malloc(sizeof(t_cmd));
			if (i == 0)
				simulate_parse1(cmd); //parse_input(&cmd, input);
			else
				simulate_parse2(cmd);
			if (cmd != NULL)
				g_status = handle_cmd(cmd, env);
			// remove_cmd(cmd);
			// sig handle
			//*input = 0;
			printf("ret : %d\n", g_status);
			i++;
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
