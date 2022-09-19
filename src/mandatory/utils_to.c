/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:30:42 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/19 13:02:45 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	close_pipes(int fd[2])
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

void	err_return(char **cmd, int *fd)
{
	char	*err;
	int		i;

	if (!cmd)
		ft_putstr_fd("Command '' not found\n", 2);
	else
	{
		err = ft_strjoin(cmd[0], ": Command not found\n");
		ft_putstr_fd(err, 2);
		free(err);
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
	close_pipes(fd);
}