/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:26:19 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/20 12:05:53 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*return_value(char *buffer, char *line, char *limiter, char *stash)
{
	free(buffer);
	if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
	{
		free(stash);
		free(line);
		return (NULL);
	}
	return (line);
}
