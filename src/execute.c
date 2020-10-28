#include <minishell.h>

// execute_input(input, env)

int		execute_cmd(t_cmd *cmd, t_env *env)
{
	t_builtin	*builtin;

	// errno = 0;
	if (validate_output_redirects(cmd) == 1 ||
		validate_input_redirects(cmd) == 1)
		return (g_status = 1);
	if ((builtin = get_builtin(cmd->name)) != NULL)
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
	//return ((errno = g_status));
	return (g_status);
}
