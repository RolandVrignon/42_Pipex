/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/20 12:49:00 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	first_cmd(t_pipex *pipex)
{
	int filein; 

	filein = open(pipex->av[1], O_RDONLY);
	if (filein == -1)
	{
		perror(pipex->av[1]);
		close_pipes(pipex->fd);
		return (0);
	}
	dup2(filein, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	return (1);
}

int	heredoc(t_pipex *pipex)
{
	char 	*line;

	ft_putstr_fd("> ", 2);
	line = get_next_line(0, pipex->av[2]);
	while (line)
	{
		write(pipex->fd[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("> ", 2);
		line = get_next_line(0, pipex->av[2]);
	}
	close(pipex->fd[0]);
	return (0);
}

int	last_cmd(t_pipex *pipex)
{
	int fileout;

	if (pipex->heredoc)
		fileout = open(pipex->av[pipex->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fileout = open(pipex->av[pipex->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
	{
		perror(pipex->av[pipex->ac - 1]);
		close_pipes(pipex->fd);
		exit(EXIT_FAILURE);
	}
	dup2(pipex->oldfd, STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(pipex->fd[1]);
	return (1);
}

int	handle_fd(t_pipex *pipex)
{
	if (pipex->i == 2 && !pipex->heredoc)
		return (first_cmd(pipex));
	else if(pipex->i == 2 && pipex->heredoc)
		return (heredoc(pipex));
	else if (pipex->i == pipex->ac - 2)
		return (last_cmd(pipex));
	else
	{
		dup2(pipex->oldfd, STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		return (1);
	}
}

void	child_process(t_pipex *pipex)
{
	if (handle_fd(pipex))
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
		if (pipex->pid > 0 && pipex->i < pipex->ac)
		{	
			if (pipex->heredoc && pipex->i == 2)
				wait(0);
			close(pipex->fd[1]);
			if (pipex->oldfd > 0)
				close(pipex->oldfd);
			pipex->oldfd = pipex->fd[0];
			pipex->i++;
			process(pipex);
		}
		wait(0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex *pipex;

	if (!check_path(envp))
		return (0);
	pipex = set_pipex(ac, av, envp);
	if (ac >= 5)
		process(pipex);
	else
		ft_putstr_fd("Too few or too many arguments\n", 2);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->oldfd);
	free(pipex);
	return (0);
}
