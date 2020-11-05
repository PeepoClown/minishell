#include <minishell.h>

static	bool	is_digital_arg(char *arg)
{
	bool	is_sign;

	is_sign = false;
	while (*arg == ' ')
		arg++;
	if (*arg == '-' || *arg == '+')
	{
		is_sign = true;
		++arg;
	}
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		is_sign = false;
		arg++;
	}
	return (!is_sign);
}

int				ft_exit(t_cmd *cmd, t_env *env)
{
	int		ret;
	int		args_count;

	env = NULL;
	ft_putstr_fd(cmd->name, 2);
	ft_putendl_fd(2);
	args_count = 0;
	while (*(cmd->args + args_count) != NULL)
		args_count++;
	if (args_count == 0)
		ret = g_status;
	else if ((!is_digital_arg(*(cmd->args))) & (ret = 255))
		ft_error(cmd->name, *(cmd->args), "numeric argument required");
	else
	{
		if (args_count > 1)
		{
			ft_error(cmd->name, NULL, "too many arguments");
			return (1);
		}
		else
			ret = (unsigned char)ft_atoi(*(cmd->args));
	}
	exit(ret);
}
