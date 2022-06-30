/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 15:45:45 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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

t_pipex set_pipex(int ac, char **av, char **envp)
{
    t_pipex pipex;
    t_pipex err;

    err.cmd = NULL;
    pipex.cmd_nbr = ac - 3;
    pipex.infile = av[1];
    pipex.outfile = av[ac - 1];
    pipex.pipe_nbr = ac - 4;
    pipex.env_path = get_envp(envp);
    pipex.opt = get_opt(ac - 3, av);
    pipex.cmd = get_cmd(ac - 3, av);
    pipex.cpath = get_paths(pipex);
    pipex.pfd = (int *)malloc(sizeof(int) * 2 * pipex.pipe_nbr);
    if (!pipex.cmd || !pipex.opt || !pipex.cpath || !pipex.pfd)
    {
        free_stuff(pipex);
        return (err);
    }
    return (pipex);
}

int main(int ac, char **av, char **envp)
{
    t_pipex pipex;

    pipex = set_pipex(ac, av, envp);
    if (!pipex.cmd)
        return 1;
    int i = 0;
    while (i < pipex.cmd_nbr) 
    {
        ft_printf("i = %d\t||\tcommand : %s\t||\toption : %s\t||\tpath : %s\n",i, pipex.cmd[i], pipex.opt[i], pipex.cpath[i]);
        i++;
    }
    // if (create_pipes(pipex))
    //     return 1;
    free_stuff(pipex);
    return 0;
}