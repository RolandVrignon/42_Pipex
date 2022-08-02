/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/02 16:58:06 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	close(0);
	close(1);
	close(2);
}

void	child_process(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY, 0777);
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

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror(av[4]);
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(av[3], envp, fd);
}

void	process(char **av, char **envp)
{
	pid_t	pid1;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error\n", 2);
		close_pipes(fd);
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		child_process(av, envp, fd);
	waitpid(pid1, NULL, 0);
	parent_process(av, envp, fd);
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;

	paths = find_path(envp);
	if (!paths)
	{	
		ft_printf("Env error\n");
		return (0);
	}
	else
		free_double(paths);
	if (ac == 5)
		process(av, envp);
	else
		ft_putstr_fd("Too few or too many arguments\n", 2);
	return (0);
}
