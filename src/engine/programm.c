/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:02:07 by wupdegra          #+#    #+#             */
/*   Updated: 2020/11/07 22:09:06 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char	*replace_to_home(char *cmd)
{
	char	*res;
	char	*cuted_path;

	if (cmd[0] != '~')
	{
		res = ft_strdup(cmd);
		free(cmd);
		return (res);
	}
	if (!ft_strcmp(cmd, "~"))
		res = ft_strdup(g_home);
	else
	{
		cuted_path = ft_substr(cmd, 1, ft_strlen(cmd));
		res = ft_strjoin(g_home, cuted_path);
		free(cuted_path);
	}
	free(cmd);
	return (res);
}

static	int		prepare_child_proc(t_cmd *cmd, t_env *env,
	char ***args_matrix, char ***env_matrix)
{
	struct stat stat_buff;

	if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
	{
		ft_error("dup", NULL, strerror(errno));
		return (errno);
	}
	if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
	{
		ft_error("dup", NULL, strerror(errno));
		return (errno);
	}
	alloc_check(*env_matrix = get_env_matrix(env));
	alloc_check(*args_matrix = get_args_matrix(cmd->name, cmd->args));
	alloc_check(cmd->name = replace_to_home(cmd->name));
	stat(cmd->name, &stat_buff);
	if (S_ISDIR(stat_buff.st_mode) == true)
	{
		ft_error(cmd->name, NULL, "is a directory");
		ft_remove_char_matrix(*args_matrix);
		ft_remove_char_matrix(*env_matrix);
		exit(126);
	}
	return (0);
}

static	int		check_sig_quit(pid_t pid)
{
	int		sig;

	if (WIFSIGNALED(pid))
	{
		sig = WTERMSIG(pid);
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3", 2);
			ft_putendl_fd(2);
		}
		return (sig + 128);
	}
	return (WEXITSTATUS(pid));
}

static	void	execute_init(char ***env_matrix, char ***args_matrix,
	t_cmd *cmd, t_env *env)
{
	*env_matrix = NULL;
	*args_matrix = NULL;
	set_path_env_var(env, cmd->name);
}

int				execute_programm(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		ret;
	char	**env_matrix;
	char	**args_matrix;

	execute_init(&env_matrix, &args_matrix, cmd, env);
	g_pid = fork();
	if ((pid = g_pid) < 0)
	{
		ft_error("fork", NULL, strerror(errno));
		return (errno);
	}
	else if (pid > 0)
		wait(&pid);
	else
	{
		if ((ret = prepare_child_proc(cmd, env, &args_matrix, &env_matrix)) > 0)
			exit(ret);
		execve(cmd->name, args_matrix, env_matrix);
		ft_remove_char_matrix(args_matrix);
		ft_remove_char_matrix(env_matrix);
		exit(programm_error(cmd->name));
	}
	return (check_sig_quit(pid));
}
