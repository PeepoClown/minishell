#include "../include/minishell.h"

char    *g_user;
char    *g_home;


int     main(int argc, char **argv, char **env)
{
	t_env   *env_list;
	char    *input;

	if (argc > 1)
		return (ft_error(1, "too much arguments passed to shell"));
	if (!(env_list = create_env(env)))
		ft_error(ENOMEM, "allocation error");
	// argc & argv usage
	// signals handling
	init_prompt_vars(&g_user, &g_home, env_list);
	input = ft_strdup("");
	while (true)
	{
//		display_prompt();
//		input = user_input();
//		printf("input : %s\n", input);
//		free(input);
		// parsing
		// execute_input(input, env);
        t_cmd cmd;
        cmd.name = "asd";
        cmd.fd_in= 0;
        cmd.fd_out = 1;
        cmd.next = NULL;
        char *args[] = { "-l", "-a" , NULL };
        cmd.args = args;
		execute_cmd(&cmd, env_list);
		break ;
	}
	remove_env(&env_list);
	remove_prompt_vars(g_user, g_home);
	return (0);
}
