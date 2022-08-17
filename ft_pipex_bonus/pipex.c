/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/18 01:51:13 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	first_cmd(t_pipex *pipex)
{
	int filein;

	filein = open(pipex->av[1], O_RDONLY);
	if (filein == -1)
	{
		perror(pipex->av[1]);
		close_pipes(pipex->fd);
		exit(EXIT_FAILURE);
	}
	dup2(filein, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
}

void	handle_fd(t_pipex *pipex)
{
	if (pipex->i == 2)
		first_cmd(pipex);
	else if (pipex->i == pipex->ac - 2)
		last_cmd(pipex);
	else
	{
		dup2(pipex->oldfd, STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
	}
}

void	last_cmd(t_pipex *pipex)
{
	int fileout;

	fileout = open(pipex->av[pipex->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
	{
		perror(pipex->av[pipex->ac]);
		close_pipes(pipex->fd);
		exit(EXIT_FAILURE);
	}
	dup2(pipex->oldfd, STDIN_FILENO);
	dup2(pipex->fd[0], pipex->oldfd);
	dup2(fileout, STDOUT_FILENO);
	close(pipex->fd[1]);
}

void	child_process(t_pipex *pipex)
{
	handle_fd(pipex);
	execute(pipex->av[pipex->i], pipex->envp);
}

void	process(t_pipex *pipex)
{
	if (pipex->i < pipex->ac - 1)
	{
		if (pipe(pipex->fd) == -1)
			return ;
		pipex->pid = fork();
		if (pipex->pid < 0)
			error();
		if (pipex->pid == 0)
			child_process(pipex);
		if (pipex->pid > 0)
		{
			close(pipex->fd[1]);
			if (pipex->oldfd > 0)
				close(pipex->oldfd);
			pipex->oldfd = pipex->fd[0];
			pipex->i++;
			process(pipex);
			wait(0);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex *pipex;

	if (!check_path(envp))
		return (0);
	pipex = set_pipex(ac, av, envp);
	if (ac >= 3)
		process(pipex);
	else
		ft_putstr_fd("Too few or too many arguments\n", 2);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->oldfd);
	free(pipex);
	return (0);
}
