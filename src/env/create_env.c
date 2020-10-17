#include <minishell.h>

t_env	*create_env(char **env_vars)
{
	t_env	*env;
	t_env	*head;

	if (!(env = create_env_item(*env_vars)))
			return (NULL);
	head = env;
	env_vars++;
	while (*env_vars != NULL)
	{
		if (!(env->next = create_env_item(*env_vars)))
			return (NULL);
		env = env->next;
		env_vars++;
	}
	return (head);
}
