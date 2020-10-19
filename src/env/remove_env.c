#include <minishell.h>

void    remove_env(t_env **env)
{
    t_env *list;
    t_env *tmp;

    list = *env;
    while (list != NULL)
    {
        tmp = list;
        list = list->next;
        del_env_item(tmp);
    }
    *env = NULL;
}
