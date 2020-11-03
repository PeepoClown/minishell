#include <minishell.h>

static	void	on_sig_int(void)
{
	if (g_pid > 0)
	{
		kill(g_pid, 2);
		ft_putendl_fd(1);
		return ;
	}
	else if (iscommand && g_pid != 0)
	{
		g_status = 1;
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putendl_fd(1);
		display_prompt();
		ft_putendl_fd(1);
	}
}

static	void	on_sig_quit(void)
{
	if (g_pid > 0)
		kill(g_pid, 3);
}

void			signals_handler(int sig)
{
	if (sig == SIGINT)
		on_sig_int();
	else if (sig == SIGQUIT)
		on_sig_quit();
	else
		return ;
}
