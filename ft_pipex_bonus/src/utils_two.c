/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:07:13 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/01 18:02:25 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_pipex	*set_pipex(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		heredoc;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		return (0);
	heredoc = 0;
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
		heredoc++;
	pipex->ac = ac;
	pipex->av = av;
	pipex->envp = envp;
	pipex->i = 2;
	pipex->oldfd = -1;
	pipex->heredoc = heredoc;
	return (pipex);
}

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	print(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}
