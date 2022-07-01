/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/01 16:38:17 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_test(t_pipex pipex)
{
	int	i;

	i = 0;
	ft_printf("PIPEEEEX\n");
	ft_printf("Nb cmd\t:\t%d\n", pipex.cmd_nbr);
	ft_printf("infile\t:\t%d\n", pipex.infile_fd);
	ft_printf("outfile\t:\t%d\n", pipex.outfile_fd);
	while (pipex.cmd[i])
	{
		ft_printf("i = %d\t||\tcommand : %s\t||\toption : %s\t\t||\tpath : %s\n",
			i, pipex.cmd[i], pipex.opt[i], pipex.cpath[i]);
		i++;
	}
}

int	here_doc(char *limiter)
{
	int		fd;
	char	*line;

	fd = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 777);
	line = get_next_line(0);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)))
	{
		write(fd, line, ft_strlen(line));
		line = get_next_line(0);
	}
	close(fd);
	return (1);
}

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
		return (1);
	if (!main_util(pipex, envp))
		return (1);
	if (heredoc)
		unlink("tmp.txt");
	free_stuff(pipex);
	return (0);
}
