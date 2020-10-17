#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	if (argc > 1)
		return (1); // error
	// handle signals
	t_env *env = create_env(envp);
	char *input;
	while (true)
	{
		display_prompt(env);
		input = user_input();
		printf("user input : %s\n", input);
		//free(input);
	}
}
