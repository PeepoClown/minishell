#include <minishell.h>

t_env	*create_env_item(const char *line)
{
	t_env	*item;

	if (!(item = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	item->key = ft_substr(line, 0, ft_find_first_of(line, '='));
	item->value = ft_substr(line, ft_find_first_of(line, '=') + 1,
		ft_strlen(line));
	item->next = NULL;
	return (item);
}

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
