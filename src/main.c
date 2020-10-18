#include "minishell.h"


int		main(int argc, char **argv, char **envp)
{
	if (argc > 1)
		return (1); // error
	// handle signals
	t_env *env = create_env(envp);
	char *input = NULL;
	// while (true)
	// {
	// 	display_prompt(env);
	// 	input = user_input();
	// 	printf("user input : %s\n", input);
	// 	free(input);
	// }

	/*t_cmd cmd;
	cmd.name = "cd";
	cmd.fd_in= 0;
	cmd.fd_out = 1;
	cmd.next = NULL;
	char *args[] = { NULL };
	cmd.args = args;
	int ret = ft_cd(&cmd, env);
	char buff[4096];
	printf("curr dir : %s\n", getcwd(buff, PATH_MAX));
	printf("return : %d\n", ret);*/
	
	/*t_cmd cmd;
	cmd.name = "echo";
	cmd.fd_in= 0;
	cmd.fd_out = 1;
	cmd.next = NULL;
	char *args[] = { "-na", "zxc", "asd", "  qwe", NULL };
	cmd.args = args;
	int ret = ft_echo(&cmd, env);
	printf("return : %d\n", ret);*/

	/*t_cmd cmd;
	cmd.name = "export";
	cmd.fd_in= 0;
	cmd.fd_out = 1;
	cmd.next = NULL;
	char *args[] = { "asd=123", NULL };
	cmd.args = args;
	int ret = ft_export(&cmd, env);
	printf("return : %d\n", ret);

	cmd.name = "export";
	cmd.fd_in= 0;
	cmd.fd_out = 1;
	cmd.next = NULL;
	char *args2[] = { "asd=", NULL };
	cmd.args = args2;
	ret = ft_export(&cmd, env);
	printf("return : %d\n", ret);
	
	cmd.name = "unset";
	cmd.fd_in= 0;
	cmd.fd_out = 1;
	cmd.next = NULL;
	char *args3[] = { "as", NULL };
	cmd.args = args3;
	ret = ft_unset(&cmd, env);
	printf("return : %d\n", ret);
	print_env_export(env, 1);*/
	
	t_cmd cmd;
	cmd.name = "ls";
	cmd.fd_in= 0;
	cmd.fd_out = 1;
	cmd.next = NULL;
	char *args[] = { "-l", NULL };
	cmd.args = args;
	execute(&cmd, env, envp);
	
	return (0);
}
