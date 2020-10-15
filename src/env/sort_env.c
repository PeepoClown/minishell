#include <minishell.h>

void	swap_env_items(t_env *item1, t_env *item2)
{
	char	*key;
	char	*value;

	key = item1->key;
	value = item1->value;
	item1->key = item2->key;
	item1->value = item2->value;
	item2->key = key;
	item2->value = value;
}

void	sort_env(t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	if ((env == NULL) || (*env == NULL))
		return ;
	tmp = *env;
	while (tmp != NULL)
	{
		curr = *env;
		while (curr->next != NULL)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
				swap_env_items(curr, curr->next);
			curr = curr->next;
		}
		tmp = tmp->next;
	}
}
