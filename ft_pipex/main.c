/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 16:00:52 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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

void print_test(t_pipex pipex)
{
    int i = 0;
    ft_printf("PIPEEEEX\n");
    ft_printf("Nb cmd : %d\n", pipex.cmd_nbr);
    ft_printf("infile : %s\n", pipex.infile);
    ft_printf("outfile : %s\n", pipex.outfile);
    while (pipex.cmd[i]) 
    {
        ft_printf("i = %d\t||\tcommand : %s\t||\toption : %s\t||\tpath : %s\n",i, pipex.cmd[i], pipex.opt[i], pipex.cpath[i]);
        i++;
    }
}

int main(int ac, char **av, char **envp)
{
    t_pipex pipex;

    pipex = set_pipex(ac, av, envp);
    if (!pipex.cmd)
        return 1;
    print_test(pipex);
    if (!create_pipes(pipex))
        return 1;
    close_pipes(pipex);
    free_stuff(pipex);
    return 0;
}