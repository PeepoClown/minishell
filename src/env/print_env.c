#include <minishell.h>

void	print_env_export(t_env *env, int fd_out)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "_") == 0)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(env->key, fd_out);
		ft_putstr_fd("=\"", fd_out);
		ft_putstr_fd(env->value, fd_out);
		ft_putstr_fd("\"", fd_out);
		ft_putendl_fd(fd_out);
		env = env->next;
	}
}
