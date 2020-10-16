#include "include/minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_env *env = create_env(envp);
	char *args[] = { "1asd=asd", NULL };
	// fckng OLDPWD
	ft_export(env, 1, 0, args);
	char *args2[] = { NULL };
	ft_export(env, 1, 0, args2);
	return (0);
}
