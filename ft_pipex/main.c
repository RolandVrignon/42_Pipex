/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/29 19:22:05 by rvrignon         ###   ########.fr       */
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
    while (paths[i++])
    {
        cmd_path = ft_strjoin(paths[i], cmd);
        if (access(cmd_path, F_OK | X_OK) == 0)
            return (cmd_path);
        free(cmd_path);
    }
    return (NULL);
}

char *get_envp(char **envp)
{
    char *envp_PATH;
    int i;

    i = 0;
    while (envp[i++])
    {
        envp_PATH = ft_strnstr(envp[i], "PATH=", 5);
        if (envp_PATH)
        {
            envp_PATH = ft_substr(envp_PATH, 5, ft_strlen(envp_PATH));
            if (!envp_PATH)
                return (0);
            break;
        }
    }
    return (envp_PATH);
}

int create_pipes(t_pipex *pipex)
{
    int i;

    i = 0;
    pipex->pfd = malloc(sizeof(int) * pipex->cmd_nbr * 2);
    if (!pipex->pfd)
        return (0);
    while (i < pipex->pipe_nbr)
    {
        if (pipe(pipex->pfd + (2 * i)) < 0)
            return (0);
        i++;
    }
    return (1);
}

char **get_paths(t_pipex *pipex, char **cmd, char **envp)
{
    char **tab;
    int i;
    char *envpath;

    envpath = get_envp(envp);
    tab = malloc(sizeof(char *) * (pipex->cmd_nbr + 1));
    if (!tab)
        return (NULL);
    i = 0;
    while (i < pipex->cmd_nbr)
    {
        tab[i] = get_cmd_path(cmd[i], envpath);
        if (!tab[i])
            return (NULL);
        i++;
    }
    return (tab);
}

char **get_cmd(int cmd_nbr, char **av)
{
    int i;
    int j;
    char **tab;
    char **split;

    i = 0;
    j = 2;
    tab = malloc(sizeof(char) * (cmd_nbr + 2));
    if (!tab)
        return (NULL);
    while (i < cmd_nbr)
    {
        split = ft_split(av[j], ' ');
        if (!split)
            return (NULL);
        tab[i] = split[0];
        free(split);
        j++;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

char **get_opt(int cmd_nbr, char **av)
{
    int i;
    int j;
    char **tab;
    char **split;

    i = 0;
    j = 2;
    tab = malloc(sizeof(char) * (cmd_nbr + 2));
    if (!tab)
        return (NULL);
    while (i < cmd_nbr)
    {
        split = ft_split(av[j], ' ');
        if (!split)
            return (NULL);
        tab[i] = split[1];
        free(split);
        j++;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

t_pipex *set_pipex(int ac, char **av, char **envp)
{
    t_pipex *pipex;

    (void)envp;
    pipex = malloc(sizeof(t_pipex *) * 1);
    if (!pipex)
        return (NULL);
    pipex->cmd_nbr = ac - 3;
    pipex->infile = av[1];
    pipex->outfile = av[ac - 1];
    pipex->pipe_nbr = ac - 4;
    pipex->opt = get_opt(ac - 3, av);
    pipex->cmd = get_cmd(ac - 3, av);
    pipex->cpath = get_paths(pipex, pipex->cmd, envp);
    if (!pipex->cmd || !pipex->opt)
        return (NULL);
    return (pipex);
}

int free_stuff(t_pipex *pipex)
{
    free(pipex->pfd);
    free(pipex);
    return (1);
}

int main(int ac, char **av, char **envp)
{
    t_pipex *pipex;

    pipex = set_pipex(ac, av, envp);
    if (!pipex)
        return 1;
    int i = 0;
    while (i < pipex->cmd_nbr)
    {
        ft_printf("i = %d\t||\tcommand : %s\t||\toption : %s\t||\tpath : %s\n",i, pipex->cmd[i], pipex->opt[i], pipex->cpath[i]);
        i++;
    }
    // if (create_pipes(pipex))
    //     return 1;
    // free_stuff(pipex);
    return 0;
}