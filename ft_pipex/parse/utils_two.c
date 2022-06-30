/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:47:45 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 15:48:03 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char **get_opt(int cmd_nbr, char **av)
{
    int i;
    char **tab;
    char **split;

    i = 0;
    tab = malloc(sizeof(char *) * (cmd_nbr + 1));
    if (!tab)
        return (NULL);
    while (i < cmd_nbr)
    {
        split = ft_split(av[i + 2], ' ');
        if (!split)
            return (NULL);
        tab[i] = ft_strdup(split[1]);
		free_double(split);
        i++;
    }
    tab[i] = 0;
    return (tab);
}

char *get_cmd_path(char *cmd, char *envp_PATH)
{
    char **paths;
    char *tmp;
    char *cmd_path;
    int i;

    paths = ft_split(envp_PATH, ':');
    if (!paths)
        return (0);
    i = 0;
    while (paths[i])
    {
        tmp = paths[i];
        paths[i] = ft_strjoin(paths[i], "/");
        free(tmp);
        i++;
    }
    i = 0;
    while (paths[i])
    {
        cmd_path = ft_strjoin(paths[i], cmd);
        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            free_double(paths);
            return (cmd_path);
        }
        free(cmd_path);
        i++;
    }
    return (NULL);
}

char **get_paths(t_pipex pipex)
{
    char **tab;
    int i;
    
    tab = malloc(sizeof(char *) * (pipex.cmd_nbr + 1));
    if (!tab)
        return (NULL);
    i = 0;
    while (i < pipex.cmd_nbr)
    {
        tab[i] = get_cmd_path(pipex.cmd[i], pipex.env_path);
        if (!tab[i])
            return (NULL);
        i++;
    }
    tab[i] = 0;
    return (tab);
}

void print_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        ft_printf("%d : %s\n", i, tab[i]);
        i++;
    }
}
