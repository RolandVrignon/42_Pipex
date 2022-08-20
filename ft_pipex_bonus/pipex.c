/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/20 16:10:18 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

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
	t_pipex	*pipex;

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
