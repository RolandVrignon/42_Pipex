/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:50:01 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 16:00:48 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int create_pipes(t_pipex pipex)
{
    int i;

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
	while(i < pipex.pipe_nbr * 2)
	{
		close (pipex.pfd[i]);
		i++;
	}
}