/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/01 14:46:21 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	first_child(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein == -1)
	{
		perror(av[1]);
		close_pipes(fd);
		exit(EXIT_FAILURE);
	}
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(av[2], envp, fd);
}

void	second_child(char **av, char **envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
	{
		perror(av[4]);
		close_pipes(fd);
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(av[3], envp, fd);
}

void	process(char **av, char **envp, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		first_child(av, envp, fd);
	if (pid > 0)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Error\n", 2);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			second_child(av, envp, fd);
		wait(0);
	}
}

static int	usage(void)
{
	ft_putstr_fd("Error : Too few or too many arguments\n\n", 2);
	ft_putstr_fd("Pipe example :\n", 2);
	ft_putstr_fd(">$ < infile cmd1 | cmd2 > outfile\n", 2);
	ft_putstr_fd(">$ ./pipex infile cmd1 cmd2 outfile\n\n", 2);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];

	if (ac != 5)
		return (usage());
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error\n", 2);
		close_pipes(fd);
		exit(EXIT_FAILURE);
	}
	process(av, envp, fd);
	close_pipes(fd);
	return (0);
}
