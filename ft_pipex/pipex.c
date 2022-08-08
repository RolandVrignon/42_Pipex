/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 14:18:08 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	child_process(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein == -1)
	{
		perror(av[1]);
		close_pipes(fd);
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(av[2], envp, fd);
}

void	parent_process(char **av, char **envp, int *fd)
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
		child_process(av, envp, fd);
	if (pid > 0)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Error\n", 2);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			parent_process(av, envp, fd);
		wait(0);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	int		fd[2];

	paths = find_path(envp);
	if (!paths)
	{	
		ft_printf("Env error\n");
		return (0);
	}
	else
		free_double(paths);
	if (ac == 5)
	{
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("Error\n", 2);
			close_pipes(fd);
			exit(EXIT_FAILURE);
		}
		process(av, envp, fd);
		close_pipes(fd);
	}
	else
		ft_putstr_fd("Too few or too many arguments\n", 2);
	return (0);
}
