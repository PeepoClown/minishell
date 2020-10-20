#include <minishell.h>

// execute_input(input, env)

int		execute_cmd(t_cmd *cmd, t_env *env)
{
	t_builtin	*builtin;
	int			status;

	errno = 0;
	builtin = get_builtin(cmd->name);
	if (builtin != NULL)
	{
		status = builtin->func(cmd, env);
		free(builtin->cmd);
		free(builtin);
	}
	else if (validate_non_builtin_cmd(cmd, env) == true)
		status = execute_programm(cmd, env);
	else
	{
		ft_error(cmd->name, NULL, "command not found");
		status = 127;
	}
	return ((status != 0) ? (errno = status) : status);
}
