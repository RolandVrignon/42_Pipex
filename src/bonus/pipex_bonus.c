/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/13 14:12:48 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	child_process(t_pipex *pipex)
{
	if (handle_fd(pipex))
		execute(pipex->av[pipex->i], pipex->envp, pipex->fd);
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

static int	usage(void)
{
	ft_putstr_fd("Error : Too few arguments\n\n", 2);
	ft_putstr_fd("Multiple pipe example (min arg required 5) :\n", 2);
	ft_putstr_fd(">$ < infile cmd1 | cmd2 | cmd3 > outfile\n", 2);
	ft_putstr_fd(">$ ./pipex infile cmd1 cmd2 cmd3 outfile\n\n", 2);
	ft_putstr_fd("Heredoc example (min arg required 6) :\n", 2);
	ft_putstr_fd(">$ cm1 << limiter | cmd2 | cmd3 >> outfile\n", 2);
	ft_putstr_fd(">$ ./pipex here_doc limiter cmd1 cmd2 cmd3 outfile\n\n", 2);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;

	if (ac > 1)
	{
		if ((ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0 && ac < 6)
			|| (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) != 0 && ac < 5))
			return (usage());
	}
	else
		return (usage());
	pipex = set_pipex(ac, av, envp);
	process(pipex);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->oldfd);
	free(pipex);
	return (0);
}
