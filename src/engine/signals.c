#include <minishell.h>

static	void	on_sig_int(void)
{
	if (g_pid > 0)
	{
		kill(g_pid, 2);
		return ;
	}
	if (g_pid != 0)
	{
		ft_putendl_fd(1);
		display_prompt();
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
