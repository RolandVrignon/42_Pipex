/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:21:48 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/11 22:54:18 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	handle_infile(char **av, int heredoc)
{
	int fd;
	
	if (heredoc)
		fd = open("tmp.txt", O_RDONLY);
	else
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		if (heredoc)
			perror("tmp.txt");
		else
			perror(av[1]);
	}
	else
		return (fd);
	return (-1);
}

static int	handle_outfile(int ac, char **av, int heredoc)
{
	int	fd;

	if (heredoc)
		fd = open(av[ac - 1], O_APPEND | O_WRONLY);
	else
		fd = open(av[ac - 1], O_TRUNC | O_WRONLY);
	if (fd < 0)
	{
		fd = open(av[ac - 1], O_TRUNC | O_APPEND | O_CREAT | O_WRONLY, 0777);
		if (fd < 0)
			perror(av[ac - 1]);
		else
		{
			close(fd);
			if (heredoc)
				fd = open(av[ac - 1], O_APPEND | O_WRONLY);
			else
				fd = open(av[ac - 1], O_TRUNC | O_WRONLY);
			return (fd);
		}
	}
	else
		return (fd);
	return (-1);
}

t_pipex	*set_pipex(int ac, char **av, char **envp, t_pipex *pipex)
{
	int heredoc;
	
	heredoc = pipex->heredoc;
	pipex->cmd_nbr = ac - (3 + heredoc);
	pipex->infile_fd = handle_infile(av, heredoc);
	pipex->outfile_fd = handle_outfile(ac, av, heredoc);
	if (pipex->outfile_fd < 0)
		return (NULL);
	pipex->pipe_nbr = ac - (4 + heredoc);
	pipex->env_path = get_envp(envp);
	pipex->opt = get_opt(ac - (3 + heredoc), av, (0 + heredoc));
	pipex->cmd = get_cmd(ac - (3 + heredoc), av, (0 + heredoc));
	pipex->pfd = (int *)malloc(sizeof(int) * 2 * pipex->pipe_nbr);
	if (!pipex->cmd || !pipex->opt || !pipex->pfd)
	{
		free_stuff(pipex);
		return (NULL);
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
