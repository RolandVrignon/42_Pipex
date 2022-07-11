/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/11 20:35:49 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	main_util(t_pipex pipex, char **envp)
{
	int	i;

	i = 0;
	if (!create_pipes(pipex))
		return (0);
	while (i < pipex.cmd_nbr)
	{
		create_childs(pipex, i, envp);
		i++;
	}
	close_pipes(pipex);
	return (1);
}

t_pipex	init(void)
{
	t_pipex	pipex;

	pipex.env_path = 0;
	pipex.pfd = 0;
	pipex.cmd = 0;
	pipex.opt = 0;
	return (pipex);
}

static int	finish(t_pipex pipex, int heredoc)
{
	if (pipex.infile_fd > 0)
		close(pipex.infile_fd);
	if (pipex.outfile_fd > 0)
		close(pipex.outfile_fd);
	close(0);
	close(1);
	close(2);
	free_stuff(pipex);
	if (heredoc)
		unlink("tmp.txt");
	return (0);
}

static int	arg_err(void)
{
	ft_printf("Miss arguments to work\n");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		heredoc;
	int 	i;

	if (!envp[0])
		return (0);
	if (ac < 5)
		return (arg_err());
	pipex = init();
	heredoc = ft_strncmp(av[1], "here_doc", ft_strlen(av[1]));
	if (!heredoc)
		heredoc = here_doc(av[2]);
	else
		heredoc = 0;
	pipex = set_pipex(ac, av, envp, heredoc);
	if (pipex.err)
		return (finish(pipex, heredoc));
	if (!main_util(pipex, envp))
		return (finish(pipex, heredoc));
	i = 0;
	while (i < pipex.pipe_nbr)
	{
		close(pipex.pfd[i]);
		i++;
	}
	waitpid(-1, NULL, 0);
	return (finish(pipex, heredoc));
}
