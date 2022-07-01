/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/01 16:45:22 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	main_util(t_pipex pipex, char **envp)
{
	int	i;

	i = 0;
	print_test(pipex);
	if (!create_pipes(pipex))
		return (0);
	while (i < pipex.cmd_nbr)
	{
		create_childs(pipex, i, envp);
		i++;
	}
	close_pipes(pipex);
	close(pipex.infile_fd);
	close(pipex.outfile_fd);
	return (1);
}

t_pipex	init(void)
{
	t_pipex	pipex;

	pipex.env_path = 0;
	pipex.pfd = 0;
	pipex.cmd = 0;
	pipex.opt = 0;
	pipex.cpath = 0;
	return (pipex);
}

static int	err(int heredoc)
{
	if (heredoc)
		unlink("tmp.txt");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		heredoc;

	if (ac < 2)
		return (1);
	pipex = init();
	heredoc = ft_strncmp(av[1], "here_doc", ft_strlen(av[1]));
	if (!heredoc)
		heredoc = here_doc(av[2]);
	else
		heredoc = 0;
	pipex = set_pipex(ac, av, envp, heredoc);
	if (pipex.infile_fd < 0)
		return (err(heredoc));
	if (!main_util(pipex, envp))
		return (err(heredoc));
	if (heredoc)
		unlink("tmp.txt");
	free_stuff(pipex);
	return (0);
}
