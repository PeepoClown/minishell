#include <minishell.h>

void	on_sig_int(void)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	ft_putendl_fd(1);
	display_prompt();
}

void	on_sig_quit(void)
{
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	signals_handler(int sig)
{
	if (sig == SIGINT)
		on_sig_int();
	else if (sig == SIGQUIT)
		on_sig_quit();
	else
		return ;
}
