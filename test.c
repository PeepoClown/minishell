#include "include/minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_env *env = create_env(envp);
	char *args[] = { NULL };
	ft_export(env, 1, 0, args);
	return (0);
}
