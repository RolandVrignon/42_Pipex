/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/11 22:35:47 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init(int heredoc)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->env_path = 0;
	pipex->pfd = 0;
	pipex->cmd = 0;
	pipex->opt = 0;
	pipex->heredoc = heredoc;
	return (pipex);
}

static t_pipex	*main_util(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	if (!create_pipes(pipex))
		return (NULL);
	while (i < pipex->cmd_nbr)
	{
		pipex = create_childs(pipex, i, envp);
		i++;
	}
	close_pipes(pipex);
	return (pipex);
}

static int	finish(t_pipex *pipex, int heredoc)
{
	free_stuff(pipex);
	if (pipex->infile_fd > 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd > 0)
		close(pipex->outfile_fd);
	close(0);
	close(1);
	close(2);
	if (heredoc)
		unlink("tmp.txt");
	free(pipex);
	return (0);
}

static int	arg_err(void)
{
	ft_printf("Not enough arguments\n");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		heredoc;
	int 	i;

	if (!envp[0])
		return (0);
	if (ac < 5)
		return (arg_err());
	heredoc = ft_strncmp(av[1], "here_doc", ft_strlen(av[1]));
	if (!heredoc)
		heredoc = here_doc(av[2]);
	else
		heredoc = 0;
	pipex = init(heredoc);
	if (!pipex)
		return (finish(pipex, heredoc));
	pipex = set_pipex(ac, av, envp, pipex);
	if (!pipex)
		return (finish(pipex, heredoc));
	pipex = main_util(pipex, envp);
	if (!pipex)
		return (finish(pipex, heredoc));
	i = 0;
	while (i < pipex->pipe_nbr)
	{
		close(pipex->pfd[i]);
		i++;
	}
	waitpid(-1, NULL, 0);
	return (finish(pipex, heredoc));
}
