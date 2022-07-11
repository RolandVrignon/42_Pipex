/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:50:01 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/11 16:59:27 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	create_pipes(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.pipe_nbr)
	{
		if (pipe(pipex.pfd + (2 * i)) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	close_pipes(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.pipe_nbr * 2)
	{
		close (pipex.pfd[i]);
		i++;
	}
}

void	make_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

static void	msg_pipe(char *arg)
{
	char *err = ": command not found";
	
	write(2, arg, ft_strlen(arg));
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
}

void	create_childs(t_pipex pipex, int i, char **envp)
{
	char	*opt[3];
	char	*cpath;

	opt[0] = pipex.cmd[i];
	if (!strncmp(pipex.opt[i], "pipexnull", ft_strlen(pipex.opt[i])))
		opt[1] = NULL;
	else
		opt[1] = pipex.opt[i];
	opt[2] = NULL;
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		if (i == 0)
			make_dup(pipex.infile_fd, pipex.pfd[1]);
		else if (i == pipex.cmd_nbr - 1)
			make_dup(pipex.pfd[i * 2 - 2], pipex.outfile_fd);
		else
			make_dup(pipex.pfd[i * 2 - 2], pipex.pfd[i * 2 + 1]);
		close_pipes(pipex);
		cpath = get_cmd_path(pipex.cmd[i], pipex.env_path);
		if (!cpath)
		{
			msg_pipe(pipex.cmd[i]);
			exit (1);
		}
		execve(cpath, opt, envp);
	}
}
