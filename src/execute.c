#include <minishell.h>

// execute_input(input, env)

int		execute_cmd(t_cmd *cmd, t_env *env)
{
	t_builtin	*builtin;

	errno = 0;
	builtin = get_builtin(cmd->name);
	if (builtin != NULL)
	{
		g_status = builtin->func(cmd, env);
		remove_builtin(builtin);
	}
	else if (validate_non_builtin_cmd(cmd, env) == true)
		g_status = execute_programm(cmd, env);
	else
	{
		ft_error(cmd->name, NULL, "command not found");
		g_status = 127;
	}
	return ((errno = g_status));
}
