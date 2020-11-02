#include <minishell.h>

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redir_out = NULL;
	cmd->redir_append_out = NULL;
	cmd->last_out_redir = NULL;
	cmd->last_out_redir_type = NONE;
	cmd->redir_in = NULL;
	cmd->pipe_status = false;
	cmd->builtin = NULL;
	return (cmd);
}

void	remove_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->name != NULL)
		free(cmd->name);
	// if (cmd->args != NULL)
	// 	ft_remove_char_matrix(cmd->args);
	// if (cmd->redir_out != NULL)
	// 	ft_remove_char_matrix(cmd->redir_out);
	// if (cmd->redir_append_out != NULL)
	// 	ft_remove_char_matrix(cmd->redir_append_out);
	// if (cmd->redir_in != NULL)
	// 	ft_remove_char_matrix(cmd->redir_in);
	// if (cmd->last_out_redir != NULL)
	// 	free(cmd->last_out_redir);
	if (cmd->builtin != NULL)
	{
		free(cmd->builtin->cmd);
		free(cmd->builtin);
	}
	free(cmd);
}
