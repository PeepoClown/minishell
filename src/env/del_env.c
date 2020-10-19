#include <minishell.h>

void    del_env_item(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	del_env(t_env **env, const char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || (get_env_value(*env, key) == NULL))
		return ;
	if (ft_strcmp((*env)->key, key) == 0)
	{
		tmp = (*env)->next;
		del_env_item(*env);
		*env = tmp;
	}
	else
	{
		tmp = *env;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->key, key) == 0)
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = tmp->next;
		del_env_item(tmp);
	}
}
