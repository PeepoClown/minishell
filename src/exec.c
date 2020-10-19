#include "../include/minishell.h"

void    execute_input(char *input, t_env *env)
{

}

t_builtin *alloc_builtins(const t_builtin *_builtins)
{
    t_builtin *builtins;
    int        i;

    builtins = (t_builtin*)malloc(sizeof(t_builtin) * 7);
    i = 0;
    while (i < 7)
    {
        builtins[i].cmd = ft_strdup(_builtins[i].cmd);
        builtins[i].func = _builtins[i].func;
        i++;
    }
    return (builtins);
}

t_builtin *get_builtin(char *cmd_name)
{
    t_builtin   _builtins[] = { { "echo", &ft_echo }, { "cd", &ft_cd },
                                  { "pwd", &ft_pwd }, { "export", &ft_export },
                                  { "env", &ft_env }, { "unset", &ft_unset },
                                  { "exit", &ft_exit } };
    int         i;
    t_builtin   *builtins = alloc_builtins(_builtins);

    i = 0;
    while (i < 7)
    {
        if (ft_strcmp(cmd_name, builtins[i].cmd) == 0)
            return (builtins + i);
        i++;
    }
    return (NULL);
}

static char	*get_path(char *cmd_name, char **paths)
{
    char		*res;
    char		*tmp;
    int			i;
    struct stat	buff;

    i = 0;
    res = NULL;
    while (paths[i] != NULL)
    {
        paths[i] = ft_strjoin(paths[i], "/");
        tmp = paths[i];
        paths[i] = ft_strjoin(paths[i], cmd_name);
        free(tmp);
        stat(paths[i], &buff);
        if (S_ISREG(buff.st_mode) == true)
        {
            res = paths[i];
            break ;
        }
        i++;
    }
    free(paths);
    return (res);
}

bool    validate_non_builtin_cmd(t_cmd *cmd, t_env *env)
{
    struct stat stat_buff;
    char        **paths;
    char        *valid_path;
    int         i;
    char        *tmp;

    paths = ft_split(get_env_value(env, "PATH"), ':');
    valid_path = get_path(cmd->name, paths);
    if (valid_path == NULL)
        return (false);
    return (true);
}

int    execute_cmd(t_cmd *cmd, t_env *env)
{
    t_builtin   *builtin;
    int         status;

    builtin = get_builtin(cmd->name);
    if (builtin != NULL)
        status = builtin->func(cmd, env);
    else if (validate_non_builtin_cmd(cmd, env) == true)
        status = execute(cmd, env);
    else
    {
        status = 127;
        error_cmd(cmd->name, NULL, "command not found");
    }
    return (status);
}