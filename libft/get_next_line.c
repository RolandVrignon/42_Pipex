/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:26:04 by rvrignon          #+#    #+#             */
/*   Updated: 2022/05/31 17:26:23 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	char		*str;
	size_t		i;
	size_t		j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

static int	get_status(char	*stash)
{
	size_t	i;

	i = 0;
	if (stash)
	{
		while (stash[i])
		{
			if (stash[i] == '\n')
				return (0);
			i++;
		}
	}
	return (1);
}

static char	*handle_line(char *stash)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	tmp = malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (NULL);
	while (j <= i)
	{
		tmp[j] = stash[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

static char	*handle_stash(char *stash)
{
	size_t	i;
	size_t	k;
	char	*tmp;

	i = 0;
	k = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(stash) - i));
	if (!tmp)
		return (NULL);
	i++;
	while (stash[i])
		tmp[k++] = stash[i++];
	tmp[k] = '\0';
	free(stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char		*stash[1050];
	char			*buffer;
	char			*line;
	size_t			status;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	status = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	while (status && get_status(stash[fd]))
	{
		status = read(fd, buffer, BUFFER_SIZE);
		buffer[status] = '\0';
		stash[fd] = ft_strjoin_gnl(stash[fd], buffer);
	}
	line = handle_line(stash[fd]);
	stash[fd] = handle_stash(stash[fd]);
	free(buffer);
	return (line);
}
