/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:03:16 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/01 15:03:30 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_pipex	heredoc_stuff(int ac, char **av, int heredoc)
{
	t_pipex	pipex;
	t_pipex	err;

	err.cmd = NULL;
	pipex.cmd_nbr = ac - (3 + heredoc);
	if (heredoc)
		pipex.infile_fd = open("tmp.txt", O_RDONLY);
	else
		pipex.infile_fd = open(av[1], O_RDONLY);
	if (pipex.infile_fd < 0)
	{
		perror("Infile");
		free_stuff(pipex);
		return (err);
	}
	pipex.pipe_nbr = ac - (4 + heredoc);
	pipex.opt = get_opt(ac - (3 + heredoc), av, (0 + heredoc));
	pipex.cmd = get_cmd(ac - (3 + heredoc), av, (0 + heredoc));
	return (pipex);
}

t_pipex	set_pipex(int ac, char **av, char **envp, int heredoc)
{
	t_pipex	pipex;
	t_pipex	err;

	err.cmd = NULL;
	pipex = heredoc_stuff(ac, av, heredoc);
	pipex.outfile_fd = open(av[ac - 1], O_WRONLY);
	if (pipex.outfile_fd < 0)
	{
		perror(av[ac - 1]);
		free_stuff(pipex);
		return (err);
	}
	pipex.env_path = get_envp(envp);
	pipex.cpath = get_paths(pipex);
	pipex.pfd = (int *)malloc(sizeof(int) * 2 * pipex.pipe_nbr);
	if (!pipex.cmd || !pipex.opt || !pipex.cpath || !pipex.pfd
		|| pipex.outfile_fd < 0 || pipex.infile_fd < 0)
	{
		free_stuff(pipex);
		return (err);
	}
	return (pipex);
}
