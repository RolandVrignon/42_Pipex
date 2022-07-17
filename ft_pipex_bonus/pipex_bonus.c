/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:43 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/17 23:36:28 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	child_process(char *av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

static void	makejob(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

void	here_doc(char *limiter, int ac)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (ac < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		line = get_next_line(0, limiter);
		while (line)
		{
			write(fd[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(0, limiter);
		}
		exit(EXIT_SUCCESS);
	}
	else
		makejob(fd);
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	fd_in;
	int	fd_out;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			fd_out = open_file(av[ac - 1], 0);
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			fd_out = open_file(av[ac - 1], 1);
			fd_in = open_file(av[1], 2);
			dup2(fd_in, STDIN_FILENO);
		}
		while (i < ac - 2)
			child_process(av[i++], envp);
		dup2(fd_out, STDOUT_FILENO);
		execute(av[ac - 2], envp);
	}
	usage();
}
