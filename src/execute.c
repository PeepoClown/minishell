#include <minishell.h>

int		handle_cmd(t_cmd *cmd, t_env *env)
{
	t_builtin	*builtin;
	int			status;

	// errno = 0;
	status = 0;
	if (!validate_output_redirects(cmd) ||
		!validate_input_redirects(cmd))
		return (1);
	if ((cmd->builtin = get_builtin(cmd->name)) != NULL)
	{
		status = execute_command(cmd, env); // exec builtin
		remove_builtin(cmd->builtin);
	}
	else if (validate_non_builtin_cmd(cmd, env) == true)
		status = execute_command(cmd, env);
	else
	{
		ft_error(cmd->name, NULL, "command not found");
		status = 127;
	}
	return (status);
}
