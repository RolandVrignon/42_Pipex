/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 18:19:44 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex set_pipex(int ac, char **av, char **envp, int heredoc)
{
    t_pipex pipex;
    t_pipex err;

    err.cmd = NULL;
    pipex.cmd_nbr = ac - 3;
    pipex.outfile_fd = open_outdoc(av, ac, heredoc);
    pipex.infile_fd = open_indoc(av, heredoc);
    pipex.pipe_nbr = ac - 4;
    pipex.env_path = get_envp(envp);
    pipex.opt = get_opt(ac - 3, av);
    pipex.cmd = get_cmd(ac - 3, av);
    pipex.cpath = get_paths(pipex);
    pipex.pfd = (int *)malloc(sizeof(int) * 2 * pipex.pipe_nbr);
    if (!pipex.cmd || !pipex.opt || !pipex.cpath || !pipex.pfd
        || !pipex.outfile_fd || !pipex.infile_fd)
    {
        free_stuff(pipex);
        return (err);
    }
    return (pipex);
}

static void print_test(t_pipex pipex)
{
    int i = 0;
    ft_printf("PIPEEEEX\n");
    ft_printf("Nb cmd\t:\t%d\n", pipex.cmd_nbr);
    ft_printf("infile\t:\t%d\n", pipex.infile_fd);
    ft_printf("outfile\t:\t%d\n", pipex.outfile_fd);
    while (pipex.cmd[i])
    {
        ft_printf("i = %d\t||\tcommand : %s\t||\toption : %s\t||\tpath : %s\n", i, pipex.cmd[i], pipex.opt[i], pipex.cpath[i]);
        i++;
    }
}

void here_doc(char *limiter)
{
    int     fd;
    char    *line;

    fd = open("tmp.txt", O_WRONLY|O_CREAT|O_TRUNC, 777);
    line = get_next_line(0);
    while (!ft_strncmp(line, limiter, ft_strlen(limiter)))
    {
        write(fd, line, ft_strlen(line));
        ft_printf("%s", line);
        line = get_next_line(0);
    }
}

int main(int ac, char **av, char **envp)
{
    t_pipex pipex;
    int i;
    int heredoc;

    i = 0;
    heredoc = ft_strncmp(av[1], "here_doc", ft_strlen(av[1]));
    if (!heredoc)
    {
        here_doc(av[2]);
        pipex = set_pipex(ac, av, envp, heredoc);
    }
    else
        pipex = set_pipex(ac, av, envp, 1);
    if (!pipex.cmd)
        return 1;
    print_test(pipex);
    if (!create_pipes(pipex))
        return 1;
    while (i < pipex.cmd_nbr)
    {
        create_childs(pipex, i, envp);
        i++;
    }
    close_pipes(pipex);
    close(pipex.infile_fd);
    close(pipex.outfile_fd);
    if (!heredoc)
        unlink("tmp.txt");
    free_stuff(pipex);
    return 0;
}