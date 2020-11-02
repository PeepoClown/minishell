#include <minishell.h>

t_env	*create_env_item(const char *line)
{
	t_env	*item;
	int		delim_pos;

	if (!line || !(item = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	item->value = NULL;
	item->next = NULL;
	item->is_hidden = 0;
	delim_pos = ft_find_first_of(line, '=');
	if (delim_pos >= 0)
	{
		item->key = ft_substr(line, 0, delim_pos);
		item->value = ft_substr(line, delim_pos + 1, ft_strlen(line));
	}
	else
		item->key = ft_strdup(line);
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
	set_env_hidden(head, "_", 3);
	return (head);
}
