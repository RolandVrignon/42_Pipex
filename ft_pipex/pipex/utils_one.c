/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:50:01 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 16:35:24 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int create_pipes(t_pipex pipex)
{
    int i;

    i = 0;
    while (i < pipex.pipe_nbr)
    {
        if (pipe(pipex.pfd + (2 * i)) < 0)
            return (0);
        i++;
    }
    return (1);
}

void	close_pipes(t_pipex pipex)
{
	int	i;

	i = 0;
	while(i < pipex.pipe_nbr * 2)
	{
		close (pipex.pfd[i]);
		i++;
	}
}

void	make_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	create_childs(t_pipex pipex, int i, char **envp)
{
	char *options[3] = {pipex.cmd[i], pipex.opt[i], NULL};
	
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		if (i == 0)
			make_dup(pipex.infile_fd, pipex.pfd[1]);
		else if (i == pipex.cmd_nbr - 1)
			make_dup(pipex.pfd[i * 2 - 2] ,pipex.infile_fd);
		else
			make_dup(pipex.pfd[i * 2 - 2], pipex.pfd[i * 2 + 1]);
		close_pipes(pipex);
		execve(pipex.cpath[i], options, envp);
	}
}