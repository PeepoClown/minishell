#include <minishell.h>

int		ft_export(t_env *env, int fd_out, int fd_in, char **args)
{
	fd_in = 0;
	if ((args == NULL) || (*args == NULL))
	{
		sort_env(&env);
		print_env_export(env, fd_out);
		return (0);
	}
	while (*args != NULL)
	{
		
	}
}
