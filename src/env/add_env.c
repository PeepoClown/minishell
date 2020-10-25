#include <minishell.h>

void	add_env(t_env **env, const char *line)
{
	t_env	*item;

	if (!env)
		return ;
	if ((*env) == NULL)
		*env = create_env_item(line);
	else
	{
		item = *env;
		while (item->next != NULL)
			item = item->next;
		item->next = create_env_item(line);
	}
}
