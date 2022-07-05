/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:21:48 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/05 10:56:46 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_pipex	heredoc_stuff(int ac, char **av, int heredoc)
{
	t_pipex	pipex;
	t_pipex	err;

	err.infile_fd = -2;
	pipex.cmd_nbr = ac - (3 + heredoc);
	if (heredoc)
		pipex.infile_fd = open("tmp.txt", O_RDONLY);
	else
		pipex.infile_fd = open(av[1], O_RDONLY);
	if (pipex.infile_fd < 0)
	{
		if (heredoc)
			perror("tmp.txt");
		else
			perror(av[1]);
		return (err);
	}
	pipex.pipe_nbr = ac - (4 + heredoc);
	return (pipex);
}

t_pipex	set_pipex(int ac, char **av, char **envp, int heredoc)
{
	t_pipex	pipex;
	t_pipex	err;

	err.infile_fd = -2;
	pipex = heredoc_stuff(ac, av, heredoc);
	if (heredoc)
		pipex.outfile_fd = open(av[ac - 1], O_APPEND | O_WRONLY);
	else
		pipex.outfile_fd = open(av[ac - 1], O_WRONLY | O_TRUNC);
	if (pipex.outfile_fd < 0)
		perror(av[ac - 1]);
	if (pipex.infile_fd < 0 || pipex.outfile_fd < 0)
		return (err);
	pipex.env_path = get_envp(envp);
	pipex.opt = get_opt(ac - (3 + heredoc), av, (0 + heredoc));
	pipex.cmd = get_cmd(ac - (3 + heredoc), av, (0 + heredoc));
	pipex.cpath = get_paths(pipex);
	pipex.pfd = (int *)malloc(sizeof(int) * 2 * pipex.pipe_nbr);
	if (!pipex.cmd || !pipex.opt || !pipex.cpath || !pipex.pfd)
	{
		free_stuff(pipex);
		return (err);
	}
	return (pipex);
}

int	here_doc(char *limiter)
{
	int		fd;
	char	*line;

	fd = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 777);
	line = get_next_line(0);
	while (ft_strncmp(line, limiter, (ft_strlen(line) - 1)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
	return (1);
}
